#include "binance/rest_client.hpp"

#include <stdexcept>
#include <utility>

namespace binance {

const char* to_string(HttpMethod method) {
  switch (method) {
    case HttpMethod::Get:
      return "GET";
    case HttpMethod::Post:
      return "POST";
    case HttpMethod::Put:
      return "PUT";
    case HttpMethod::Delete:
      return "DELETE";
  }
  throw std::invalid_argument("unknown HTTP method");
}

QueryParams OrderRequest::params() const {
  QueryParams params{{"symbol", symbol}, {"side", side}, {"type", type}};
  append_if(params, "timeInForce", time_in_force);
  append_if(params, "quantity", quantity);
  append_if(params, "quoteOrderQty", quote_order_qty);
  append_if(params, "price", price);
  append_if(params, "newClientOrderId", new_client_order_id);
  append_if(params, "newOrderRespType", new_order_resp_type);
  append_if(params, "selfTradePreventionMode", self_trade_prevention_mode);
  params.insert(params.end(), extra_params.begin(), extra_params.end());
  return params;
}

RestClient::RestClient(std::string api_key, std::string api_secret, std::string base_url, std::string recv_window,
                       HttpOptions options)
    : http_(std::move(api_key), std::move(api_secret), std::move(base_url), std::move(recv_window),
            std::move(options)) {}

std::string RestClient::warm_up() const { return http_.warm_up(); }

std::string RestClient::request_public(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return http_.send_public(method, path, params);
}

std::string RestClient::request_api_key(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return http_.send_api_key(method, path, params);
}

std::string RestClient::request_signed(HttpMethod method, const std::string& path, const QueryParams& params) const {
  return http_.send_signed(method, path, params);
}

}  // namespace binance
