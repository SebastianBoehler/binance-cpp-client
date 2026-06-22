#include <string>

#include "binance/rest_client.hpp"

namespace binance {

std::string RestClient::ping() const { return request_public(HttpMethod::Get, "/api/v3/ping"); }

std::string RestClient::server_time() const { return request_public(HttpMethod::Get, "/api/v3/time"); }

std::string RestClient::exchange_info(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, "/api/v3/exchangeInfo", filters);
}

std::string RestClient::order_book(const std::string& symbol, int limit) const {
  return request_public(HttpMethod::Get, "/api/v3/depth", {{"symbol", symbol}, {"limit", std::to_string(limit)}});
}

std::string RestClient::recent_trades(const std::string& symbol, int limit) const {
  return request_public(HttpMethod::Get, "/api/v3/trades", {{"symbol", symbol}, {"limit", std::to_string(limit)}});
}

std::string RestClient::aggregate_trades(const std::string& symbol, const QueryParams& filters) const {
  QueryParams params{{"symbol", symbol}};
  params.insert(params.end(), filters.begin(), filters.end());
  return request_public(HttpMethod::Get, "/api/v3/aggTrades", params);
}

std::string RestClient::klines(const std::string& symbol, const std::string& interval,
                               const QueryParams& filters) const {
  QueryParams params{{"symbol", symbol}, {"interval", interval}};
  params.insert(params.end(), filters.begin(), filters.end());
  return request_public(HttpMethod::Get, "/api/v3/klines", params);
}

std::string RestClient::average_price(const std::string& symbol) const {
  return request_public(HttpMethod::Get, "/api/v3/avgPrice", {{"symbol", symbol}});
}

std::string RestClient::ticker_price(const std::optional<std::string>& symbol) const {
  QueryParams params;
  append_if(params, "symbol", symbol);
  return request_public(HttpMethod::Get, "/api/v3/ticker/price", params);
}

std::string RestClient::book_ticker(const std::optional<std::string>& symbol) const {
  QueryParams params;
  append_if(params, "symbol", symbol);
  return request_public(HttpMethod::Get, "/api/v3/ticker/bookTicker", params);
}

}  // namespace binance
