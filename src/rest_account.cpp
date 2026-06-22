#include "binance/rest_client.hpp"

namespace binance {

std::string RestClient::account_info(const std::optional<std::string>& omit_zero_balances) const {
  QueryParams params;
  append_if(params, "omitZeroBalances", omit_zero_balances);
  return request_signed(HttpMethod::Get, "/api/v3/account", params);
}

std::string RestClient::query_order(const std::string& symbol, const QueryParams& ids) const {
  QueryParams params{{"symbol", symbol}};
  params.insert(params.end(), ids.begin(), ids.end());
  return request_signed(HttpMethod::Get, "/api/v3/order", params);
}

std::string RestClient::open_orders(const std::optional<std::string>& symbol) const {
  QueryParams params;
  append_if(params, "symbol", symbol);
  return request_signed(HttpMethod::Get, "/api/v3/openOrders", params);
}

std::string RestClient::all_orders(const std::string& symbol, const QueryParams& filters) const {
  QueryParams params{{"symbol", symbol}};
  params.insert(params.end(), filters.begin(), filters.end());
  return request_signed(HttpMethod::Get, "/api/v3/allOrders", params);
}

std::string RestClient::account_trades(const std::string& symbol, const QueryParams& filters) const {
  QueryParams params{{"symbol", symbol}};
  params.insert(params.end(), filters.begin(), filters.end());
  return request_signed(HttpMethod::Get, "/api/v3/myTrades", params);
}

}  // namespace binance
