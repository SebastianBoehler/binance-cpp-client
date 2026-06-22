#include "binance/rest_client.hpp"

namespace binance {

std::string RestClient::account_info(const std::optional<std::string>& omit_zero_balances) const {
  QueryParams params;
  append_if(params, "omitZeroBalances", omit_zero_balances);
  return request_signed(HttpMethod::Get, "/api/v3/account", params);
}

std::string RestClient::account_commission(const std::string& symbol) const {
  return request_signed(HttpMethod::Get, "/api/v3/account/commission", {{"symbol", symbol}});
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

std::string RestClient::order_list(const QueryParams& ids) const {
  return request_signed(HttpMethod::Get, "/api/v3/orderList", ids);
}

std::string RestClient::open_order_lists() const { return request_signed(HttpMethod::Get, "/api/v3/openOrderList"); }

std::string RestClient::all_order_lists(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, "/api/v3/allOrderList", filters);
}

std::string RestClient::account_allocations(const std::string& symbol, const QueryParams& filters) const {
  QueryParams params{{"symbol", symbol}};
  params.insert(params.end(), filters.begin(), filters.end());
  return request_signed(HttpMethod::Get, "/api/v3/myAllocations", params);
}

std::string RestClient::account_filters(const std::string& symbol) const {
  return request_signed(HttpMethod::Get, "/api/v3/myFilters", {{"symbol", symbol}});
}

std::string RestClient::prevented_matches(const std::string& symbol, const QueryParams& filters) const {
  QueryParams params{{"symbol", symbol}};
  params.insert(params.end(), filters.begin(), filters.end());
  return request_signed(HttpMethod::Get, "/api/v3/myPreventedMatches", params);
}

std::string RestClient::order_amendments(const std::string& symbol, const std::string& order_id,
                                         const QueryParams& filters) const {
  QueryParams params{{"symbol", symbol}, {"orderId", order_id}};
  params.insert(params.end(), filters.begin(), filters.end());
  return request_signed(HttpMethod::Get, "/api/v3/order/amendments", params);
}

std::string RestClient::order_rate_limit() const { return request_signed(HttpMethod::Get, "/api/v3/rateLimit/order"); }

}  // namespace binance
