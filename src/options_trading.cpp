#include "binance/options_client.hpp"

namespace binance {

std::string OptionsClient::account_trades(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("/userTrades"), filters);
}

std::string OptionsClient::cancel_all_orders(const std::string& symbol) const {
  return request_signed(HttpMethod::Delete, endpoint("/allOpenOrders"), {{"symbol", symbol}});
}

std::string OptionsClient::cancel_all_orders_by_underlying(const std::string& underlying) const {
  return request_signed(HttpMethod::Delete, endpoint("/allOpenOrdersByUnderlying"), {{"underlying", underlying}});
}

std::string OptionsClient::cancel_batch_orders(const QueryParams& params) const {
  return request_signed(HttpMethod::Delete, endpoint("/batchOrders"), params);
}

std::string OptionsClient::cancel_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Delete, endpoint("/order"), params);
}

std::string OptionsClient::new_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("/order"), params);
}

std::string OptionsClient::positions(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("/position"), filters);
}

std::string OptionsClient::batch_orders(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("/batchOrders"), params);
}

std::string OptionsClient::open_orders(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("/openOrders"), filters);
}

std::string OptionsClient::history_orders(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("/historyOrders"), filters);
}

std::string OptionsClient::query_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("/order"), params);
}

std::string OptionsClient::commission(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("/commission"), params);
}

std::string OptionsClient::exercise_record(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("/exerciseRecord"), filters);
}

std::string OptionsClient::countdown_cancel_heartbeat(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("/countdownCancelAllHeartBeat"), params);
}

std::string OptionsClient::get_countdown_cancel_all(const std::string& underlying) const {
  return request_signed(HttpMethod::Get, endpoint("/countdownCancelAll"), {{"underlying", underlying}});
}

std::string OptionsClient::get_mmp_config(const std::string& underlying) const {
  return request_signed(HttpMethod::Get, endpoint("/mmp"), {{"underlying", underlying}});
}

std::string OptionsClient::reset_mmp_config(const std::string& underlying) const {
  return request_signed(HttpMethod::Post, endpoint("/mmpReset"), {{"underlying", underlying}});
}

std::string OptionsClient::set_countdown_cancel_all(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("/countdownCancelAll"), params);
}

std::string OptionsClient::set_mmp_config(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("/mmpSet"), params);
}

std::string OptionsClient::execute_block_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("/block/order/execute"), params);
}

std::string OptionsClient::block_trades(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("/block/user-trades"), filters);
}

std::string OptionsClient::cancel_block_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Delete, endpoint("/block/order/create"), params);
}

std::string OptionsClient::extend_block_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Put, endpoint("/block/order/create"), params);
}

std::string OptionsClient::new_block_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, endpoint("/block/order/create"), params);
}

std::string OptionsClient::query_block_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Get, endpoint("/block/order/execute"), params);
}

std::string OptionsClient::block_orders(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("/block/order/orders"), filters);
}

}  // namespace binance
