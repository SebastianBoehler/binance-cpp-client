#include "binance/options_client.hpp"

#include <utility>

namespace binance {

OptionsClient::OptionsClient(std::string api_key, std::string api_secret, std::string base_url, std::string recv_window,
                             HttpOptions options)
    : http_(std::move(api_key), std::move(api_secret), std::move(base_url), std::move(recv_window),
            std::move(options)) {}

std::string OptionsClient::warm_up() const { return http_.warm_up(); }

std::string OptionsClient::request_public(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return http_.send_public(method, path, params);
}

std::string OptionsClient::request_api_key(HttpMethod method, const std::string& path,
                                           const QueryParams& params) const {
  return http_.send_api_key(method, path, params);
}

std::string OptionsClient::request_signed(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return http_.send_signed(method, path, params);
}

std::string OptionsClient::endpoint(const std::string& path) { return "/eapi/v1" + path; }

}  // namespace binance
