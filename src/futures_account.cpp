#include "binance/futures_client.hpp"

namespace binance {

std::string FuturesClient::account_info() const {
  return request_signed(HttpMethod::Get, account_endpoint("/fapi/v3/account", "/dapi/v1/account"));
}

std::string FuturesClient::account_balance() const {
  return request_signed(HttpMethod::Get, account_endpoint("/fapi/v3/balance", "/dapi/v1/balance"));
}

std::string FuturesClient::position_mode() const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/positionSide/dual"));
}

std::string FuturesClient::income_history(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/income"), filters);
}

std::string FuturesClient::leverage_bracket(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/leverageBracket"), filters);
}

std::string FuturesClient::commission_rate(const std::string& symbol) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/commissionRate"), {{"symbol", symbol}});
}

std::string FuturesClient::order_rate_limit() const {
  require_usdm("order_rate_limit");
  return request_signed(HttpMethod::Get, endpoint("v1", "/rateLimit/order"));
}

std::string FuturesClient::position_risk(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, account_endpoint("/fapi/v3/positionRisk", "/dapi/v1/positionRisk"), filters);
}

}  // namespace binance
