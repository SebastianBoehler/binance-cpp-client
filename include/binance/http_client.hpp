#pragma once

#include <curl/curl.h>

#include <mutex>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "binance/query.hpp"
#include "binance/types.hpp"

namespace binance {

using HttpHeaders = std::vector<std::pair<std::string, std::string>>;

struct HttpOptions {
  long connect_timeout_ms = 10000;
  long request_timeout_ms = 30000;
  long dns_cache_timeout_seconds = 300;
  long max_connections = 8;
  bool share_dns_and_ssl_session_cache = true;
  bool tcp_keepalive = true;
  bool tcp_nodelay = true;
  long tcp_keepidle_seconds = 60;
  long tcp_keepintvl_seconds = 30;
  std::string proxy;
  std::string user_agent = "binance-cpp-client/0.1.0";
};

class HttpError : public std::runtime_error {
 public:
  HttpError(long status_code, std::string body, HttpHeaders headers = {});

  long status_code() const { return status_code_; }
  const std::string& body() const { return body_; }
  const HttpHeaders& headers() const { return headers_; }
  std::optional<std::string> header(const std::string& name) const;
  const std::optional<long>& api_code() const { return api_code_; }
  const std::optional<std::string>& api_message() const { return api_message_; }

 private:
  long status_code_;
  std::string body_;
  HttpHeaders headers_;
  std::optional<long> api_code_;
  std::optional<std::string> api_message_;
};

class HttpClient {
 public:
  HttpClient(std::string api_key, std::string api_secret, std::string base_url, std::string recv_window = "5000",
             HttpOptions options = {});
  ~HttpClient();

  HttpClient(const HttpClient&) = delete;
  HttpClient& operator=(const HttpClient&) = delete;
  HttpClient(HttpClient&&) = delete;
  HttpClient& operator=(HttpClient&&) = delete;

  std::string warm_up() const;
  std::string send_public(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;
  std::string send_api_key(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;
  std::string send_signed(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;

  const std::string& base_url() const { return base_url_; }
  const HttpOptions& options() const { return options_; }

 private:
  std::string send(HttpMethod method, const std::string& path, QueryParams params, bool api_key_header,
                   bool signed_request) const;
  std::string make_signed_query(QueryParams params) const;

  std::string api_key_;
  std::string api_secret_;
  std::string base_url_;
  std::string recv_window_;
  HttpOptions options_;
  mutable std::mutex curl_mutex_;
  CURL* curl_;
};

}  // namespace binance
