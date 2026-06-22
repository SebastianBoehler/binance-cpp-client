#include "binance/http_client.hpp"

#include <curl/curl.h>

#include <memory>
#include <stdexcept>
#include <utility>

#include "binance/signing.hpp"

namespace binance {
namespace {

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
  const size_t real_size = size * nmemb;
  static_cast<std::string*>(userdata)->append(ptr, real_size);
  return real_size;
}

size_t header_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
  const size_t real_size = size * nmemb;
  std::string line(ptr, real_size);
  while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
    line.pop_back();
  }
  const auto colon = line.find(':');
  if (colon == std::string::npos) {
    return real_size;
  }
  size_t value_start = colon + 1;
  while (value_start < line.size() && line[value_start] == ' ') {
    ++value_start;
  }
  static_cast<HttpHeaders*>(userdata)->emplace_back(line.substr(0, colon), line.substr(value_start));
  return real_size;
}

std::string join_url(const std::string& base, const std::string& path) {
  if (!base.empty() && base.back() == '/' && !path.empty() && path.front() == '/') {
    return base + path.substr(1);
  }
  if (!base.empty() && base.back() != '/' && !path.empty() && path.front() != '/') {
    return base + "/" + path;
  }
  return base + path;
}

void ensure_curl_global() {
  static std::once_flag once;
  std::call_once(once, [] {
    if (curl_global_init(CURL_GLOBAL_DEFAULT) != 0) {
      throw std::runtime_error("curl_global_init failed");
    }
  });
}

std::mutex& share_mutex() {
  static std::mutex mutex;
  return mutex;
}

void share_lock(CURL*, curl_lock_data, curl_lock_access, void*) { share_mutex().lock(); }

void share_unlock(CURL*, curl_lock_data, void*) { share_mutex().unlock(); }

CURLSH* shared_cache() {
  static CURLSH* handle = [] {
    CURLSH* share = curl_share_init();
    if (share == nullptr) {
      throw std::runtime_error("curl_share_init failed");
    }
    curl_share_setopt(share, CURLSHOPT_LOCKFUNC, share_lock);
    curl_share_setopt(share, CURLSHOPT_UNLOCKFUNC, share_unlock);
    curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
    curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
    return share;
  }();
  return handle;
}

void apply_options(CURL* curl, const HttpOptions& options) {
  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, options.connect_timeout_ms);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, options.request_timeout_ms);
  curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, options.dns_cache_timeout_seconds);
  curl_easy_setopt(curl, CURLOPT_MAXCONNECTS, options.max_connections);
  curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, options.tcp_keepalive ? 1L : 0L);
  curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, options.tcp_nodelay ? 1L : 0L);
  if (options.share_dns_and_ssl_session_cache) {
    curl_easy_setopt(curl, CURLOPT_SHARE, shared_cache());
  }
  if (options.tcp_keepalive) {
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, options.tcp_keepidle_seconds);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, options.tcp_keepintvl_seconds);
  }
  if (!options.proxy.empty()) {
    curl_easy_setopt(curl, CURLOPT_PROXY, options.proxy.c_str());
  }
  if (!options.user_agent.empty()) {
    curl_easy_setopt(curl, CURLOPT_USERAGENT, options.user_agent.c_str());
  }
}

struct HeaderListDeleter {
  void operator()(curl_slist* headers) const { curl_slist_free_all(headers); }
};

void append_header(std::unique_ptr<curl_slist, HeaderListDeleter>& headers, const std::string& header) {
  headers.reset(curl_slist_append(headers.release(), header.c_str()));
}

}  // namespace

HttpClient::HttpClient(std::string api_key, std::string api_secret, std::string base_url, std::string recv_window,
                       HttpOptions options)
    : api_key_(std::move(api_key)),
      api_secret_(std::move(api_secret)),
      base_url_(std::move(base_url)),
      recv_window_(std::move(recv_window)),
      options_(std::move(options)),
      curl_(nullptr) {
  ensure_curl_global();
  curl_ = curl_easy_init();
  if (curl_ == nullptr) {
    throw std::runtime_error("curl_easy_init failed");
  }
  apply_options(curl_, options_);
}

HttpClient::~HttpClient() {
  if (curl_ != nullptr) {
    curl_easy_cleanup(curl_);
  }
}

std::string HttpClient::warm_up() const { return send_public(HttpMethod::Get, "/api/v3/ping"); }

std::string HttpClient::send_public(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return send(method, path, params, false, false);
}

std::string HttpClient::send_api_key(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return send(method, path, params, true, false);
}

std::string HttpClient::send_signed(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return send(method, path, params, true, true);
}

std::string HttpClient::make_signed_query(QueryParams params) const {
  if (!has_param(params, "timestamp")) {
    params.emplace_back("timestamp", std::to_string(Signer::now_ms()));
  }
  if (!recv_window_.empty() && !has_param(params, "recvWindow")) {
    params.emplace_back("recvWindow", recv_window_);
  }
  std::string query = encode_query(params);
  params.emplace_back("signature", Signer::sign_query(api_secret_, query));
  return encode_query(params);
}

std::string HttpClient::send(HttpMethod method, const std::string& path, QueryParams params, bool api_key_header,
                             bool signed_request) const {
  const std::string query = signed_request ? make_signed_query(std::move(params)) : encode_query(params);
  std::string url = join_url(base_url_, path);
  if (!query.empty()) {
    url += "?" + query;
  }

  std::string response;
  HttpHeaders response_headers;
  std::unique_ptr<curl_slist, HeaderListDeleter> headers;
  if (api_key_header) {
    append_header(headers, "X-MBX-APIKEY: " + api_key_);
  }

  std::lock_guard<std::mutex> lock(curl_mutex_);
  curl_easy_reset(curl_);
  apply_options(curl_, options_);
  curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
  curl_easy_setopt(curl_, CURLOPT_HEADERFUNCTION, header_callback);
  curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response_headers);

  if (method == HttpMethod::Get) {
    curl_easy_setopt(curl_, CURLOPT_HTTPGET, 1L);
  } else {
    curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, to_string(method));
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, "");
  }
  if (headers) {
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers.get());
  }

  const CURLcode result = curl_easy_perform(curl_);
  long status = 0;
  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &status);
  if (result != CURLE_OK) {
    throw std::runtime_error(std::string("curl_easy_perform failed: ") + curl_easy_strerror(result));
  }
  if (status >= 400) {
    throw HttpError(status, response, std::move(response_headers));
  }
  return response;
}

}  // namespace binance
