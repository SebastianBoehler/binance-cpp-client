#include "binance/futures_client.hpp"

#include <stdexcept>
#include <utility>

namespace binance {
namespace {

const char* default_base_url(FuturesMarket market) {
  switch (market) {
    case FuturesMarket::UsdM:
      return FuturesClient::kUsdMBaseUrl;
    case FuturesMarket::CoinM:
      return FuturesClient::kCoinMBaseUrl;
  }
  throw std::invalid_argument("unknown futures market");
}

const char* endpoint_prefix(FuturesMarket market) {
  switch (market) {
    case FuturesMarket::UsdM:
      return "/fapi";
    case FuturesMarket::CoinM:
      return "/dapi";
  }
  throw std::invalid_argument("unknown futures market");
}

}  // namespace

FuturesClient::FuturesClient(FuturesMarket market, std::string api_key, std::string api_secret, std::string base_url,
                             std::string recv_window, HttpOptions options)
    : market_(market),
      prefix_(endpoint_prefix(market)),
      http_(std::move(api_key), std::move(api_secret),
            base_url.empty() ? default_base_url(market) : std::move(base_url), std::move(recv_window),
            std::move(options)) {}

std::string FuturesClient::warm_up() const { return http_.warm_up(); }

std::string FuturesClient::request_public(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return http_.send_public(method, path, params);
}

std::string FuturesClient::request_api_key(HttpMethod method, const std::string& path,
                                           const QueryParams& params) const {
  return http_.send_api_key(method, path, params);
}

std::string FuturesClient::request_signed(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return http_.send_signed(method, path, params);
}

std::string FuturesClient::endpoint(const std::string& version, const std::string& path) const {
  return prefix_ + "/" + version + path;
}

std::string FuturesClient::account_endpoint(const std::string& usdm_path, const std::string& coinm_path) const {
  return market_ == FuturesMarket::UsdM ? usdm_path : coinm_path;
}

void FuturesClient::require_usdm(const std::string& method) const {
  if (market_ != FuturesMarket::UsdM) {
    throw std::logic_error(method + " is only available on USD-M futures");
  }
}

}  // namespace binance
