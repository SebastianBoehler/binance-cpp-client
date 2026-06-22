#include "binance/rest_client.hpp"

namespace binance {

std::string RestClient::new_order(const OrderRequest& request) const {
  return request_signed(HttpMethod::Post, "/api/v3/order", request.params());
}

std::string RestClient::test_order(const OrderRequest& request) const {
  return request_signed(HttpMethod::Post, "/api/v3/order/test", request.params());
}

std::string RestClient::cancel_order(const std::string& symbol, const QueryParams& ids) const {
  QueryParams params{{"symbol", symbol}};
  params.insert(params.end(), ids.begin(), ids.end());
  return request_signed(HttpMethod::Delete, "/api/v3/order", params);
}

std::string RestClient::cancel_open_orders(const std::string& symbol) const {
  return request_signed(HttpMethod::Delete, "/api/v3/openOrders", {{"symbol", symbol}});
}

}  // namespace binance
