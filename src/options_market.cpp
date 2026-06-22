#include <string>

#include "binance/options_client.hpp"

namespace binance {
namespace {

QueryParams with_filters(QueryParams params, const QueryParams& filters) {
  params.insert(params.end(), filters.begin(), filters.end());
  return params;
}

}  // namespace

std::string OptionsClient::ping() const { return request_public(HttpMethod::Get, endpoint("/ping")); }

std::string OptionsClient::server_time() const { return request_public(HttpMethod::Get, endpoint("/time")); }

std::string OptionsClient::exchange_info() const { return request_public(HttpMethod::Get, endpoint("/exchangeInfo")); }

std::string OptionsClient::exercise_history(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("/exerciseHistory"), filters);
}

std::string OptionsClient::index_price(const std::string& underlying) const {
  return request_public(HttpMethod::Get, endpoint("/index"), {{"underlying", underlying}});
}

std::string OptionsClient::klines(const std::string& symbol, const std::string& interval,
                                  const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("/klines"),
                        with_filters({{"symbol", symbol}, {"interval", interval}}, filters));
}

std::string OptionsClient::open_interest(const QueryParams& params) const {
  return request_public(HttpMethod::Get, endpoint("/openInterest"), params);
}

std::string OptionsClient::mark_price(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("/mark"), filters);
}

std::string OptionsClient::order_book(const std::string& symbol, int limit) const {
  return request_public(HttpMethod::Get, endpoint("/depth"), {{"symbol", symbol}, {"limit", std::to_string(limit)}});
}

std::string OptionsClient::recent_block_trades(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("/blockTrades"), filters);
}

std::string OptionsClient::recent_trades(const std::string& symbol, int limit) const {
  return request_public(HttpMethod::Get, endpoint("/trades"), {{"symbol", symbol}, {"limit", std::to_string(limit)}});
}

std::string OptionsClient::ticker_24hr(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("/ticker"), filters);
}

}  // namespace binance
