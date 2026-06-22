#include <string>

#include "binance/futures_client.hpp"

namespace binance {

std::string FuturesClient::new_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("v1", "/order"), params);
}

std::string FuturesClient::usdm_test_order(const QueryParams& params) const {
  require_usdm("usdm_test_order");
  return request_signed(HttpMethod::Post, endpoint("v1", "/order/test"), params);
}

std::string FuturesClient::query_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/order"), params);
}

std::string FuturesClient::cancel_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Delete, endpoint("v1", "/order"), params);
}

std::string FuturesClient::cancel_all_open_orders(const std::string& symbol) const {
  return request_signed(HttpMethod::Delete, endpoint("v1", "/allOpenOrders"), {{"symbol", symbol}});
}

std::string FuturesClient::batch_orders(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("v1", "/batchOrders"), params);
}

std::string FuturesClient::cancel_batch_orders(const QueryParams& params) const {
  return request_signed(HttpMethod::Delete, endpoint("v1", "/batchOrders"), params);
}

std::string FuturesClient::modify_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Put, endpoint("v1", "/order"), params);
}

std::string FuturesClient::modify_batch_orders(const QueryParams& params) const {
  return request_signed(HttpMethod::Put, endpoint("v1", "/batchOrders"), params);
}

std::string FuturesClient::open_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/openOrder"), params);
}

std::string FuturesClient::open_orders(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/openOrders"), filters);
}

std::string FuturesClient::all_orders(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/allOrders"), params);
}

std::string FuturesClient::account_trades(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/userTrades"), params);
}

std::string FuturesClient::change_position_mode(bool dual_side_position) const {
  return request_signed(HttpMethod::Post, endpoint("v1", "/positionSide/dual"),
                        {{"dualSidePosition", dual_side_position ? "true" : "false"}});
}

std::string FuturesClient::change_leverage(const std::string& symbol, int leverage) const {
  return request_signed(HttpMethod::Post, endpoint("v1", "/leverage"),
                        {{"symbol", symbol}, {"leverage", std::to_string(leverage)}});
}

std::string FuturesClient::change_margin_type(const std::string& symbol, const std::string& margin_type) const {
  return request_signed(HttpMethod::Post, endpoint("v1", "/marginType"),
                        {{"symbol", symbol}, {"marginType", margin_type}});
}

std::string FuturesClient::modify_position_margin(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("v1", "/positionMargin"), params);
}

std::string FuturesClient::position_margin_history(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/positionMargin/history"), params);
}

std::string FuturesClient::order_modify_history(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/orderAmendment"), params);
}

std::string FuturesClient::countdown_cancel_all(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("v1", "/countdownCancelAll"), params);
}

std::string FuturesClient::force_orders(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/forceOrders"), filters);
}

std::string FuturesClient::adl_quantile(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("v1", "/adlQuantile"), filters);
}

}  // namespace binance
