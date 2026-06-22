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

std::string RestClient::cancel_order_list(const std::string& symbol, const QueryParams& ids) const {
  QueryParams params{{"symbol", symbol}};
  params.insert(params.end(), ids.begin(), ids.end());
  return request_signed(HttpMethod::Delete, "/api/v3/orderList", params);
}

std::string RestClient::amend_order_keep_priority(const std::string& symbol, const std::string& new_qty,
                                                  const QueryParams& ids) const {
  QueryParams params{{"symbol", symbol}, {"newQty", new_qty}};
  params.insert(params.end(), ids.begin(), ids.end());
  return request_signed(HttpMethod::Put, "/api/v3/order/amend/keepPriority", params);
}

std::string RestClient::cancel_replace_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, "/api/v3/order/cancelReplace", params);
}

std::string RestClient::order_list_oco(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, "/api/v3/orderList/oco", params);
}

std::string RestClient::order_list_oto(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, "/api/v3/orderList/oto", params);
}

std::string RestClient::order_list_otoco(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, "/api/v3/orderList/otoco", params);
}

std::string RestClient::order_list_opo(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, "/api/v3/orderList/opo", params);
}

std::string RestClient::order_list_opoco(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, "/api/v3/orderList/opoco", params);
}

std::string RestClient::sor_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, "/api/v3/sor/order", params);
}

std::string RestClient::sor_test_order(const QueryParams& params) const {
  return request_signed(HttpMethod::Post, "/api/v3/sor/order/test", params);
}

}  // namespace binance
