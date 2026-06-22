#include <string>

#include "binance/futures_client.hpp"

namespace binance {
namespace {

QueryParams with_filters(QueryParams params, const QueryParams& filters) {
  params.insert(params.end(), filters.begin(), filters.end());
  return params;
}

}  // namespace

std::string FuturesClient::ping() const { return request_public(HttpMethod::Get, endpoint("v1", "/ping")); }

std::string FuturesClient::server_time() const { return request_public(HttpMethod::Get, endpoint("v1", "/time")); }

std::string FuturesClient::exchange_info() const {
  return request_public(HttpMethod::Get, endpoint("v1", "/exchangeInfo"));
}

std::string FuturesClient::order_book(const std::string& symbol, int limit) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/depth"),
                        {{"symbol", symbol}, {"limit", std::to_string(limit)}});
}

std::string FuturesClient::recent_trades(const std::string& symbol, int limit) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/trades"),
                        {{"symbol", symbol}, {"limit", std::to_string(limit)}});
}

std::string FuturesClient::historical_trades(const std::string& symbol, const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/historicalTrades"),
                        with_filters({{"symbol", symbol}}, filters));
}

std::string FuturesClient::aggregate_trades(const std::string& symbol, const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/aggTrades"), with_filters({{"symbol", symbol}}, filters));
}

std::string FuturesClient::klines(const std::string& symbol, const std::string& interval,
                                  const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/klines"),
                        with_filters({{"symbol", symbol}, {"interval", interval}}, filters));
}

std::string FuturesClient::continuous_klines(const std::string& pair, const std::string& contract_type,
                                             const std::string& interval, const QueryParams& filters) const {
  return request_public(
      HttpMethod::Get, endpoint("v1", "/continuousKlines"),
      with_filters({{"pair", pair}, {"contractType", contract_type}, {"interval", interval}}, filters));
}

std::string FuturesClient::index_price_klines(const std::string& pair, const std::string& interval,
                                              const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/indexPriceKlines"),
                        with_filters({{"pair", pair}, {"interval", interval}}, filters));
}

std::string FuturesClient::mark_price_klines(const std::string& symbol, const std::string& interval,
                                             const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/markPriceKlines"),
                        with_filters({{"symbol", symbol}, {"interval", interval}}, filters));
}

std::string FuturesClient::premium_index_klines(const QueryParams& params) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/premiumIndexKlines"), params);
}

std::string FuturesClient::mark_price(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/premiumIndex"), filters);
}

std::string FuturesClient::funding_rate(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/fundingRate"), filters);
}

std::string FuturesClient::funding_info() const {
  return request_public(HttpMethod::Get, endpoint("v1", "/fundingInfo"));
}

std::string FuturesClient::ticker_24hr(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/ticker/24hr"), filters);
}

std::string FuturesClient::ticker_price(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/ticker/price"), filters);
}

std::string FuturesClient::book_ticker(const QueryParams& filters) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/ticker/bookTicker"), filters);
}

std::string FuturesClient::open_interest(const std::string& symbol) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/openInterest"), {{"symbol", symbol}});
}

std::string FuturesClient::constituents(const QueryParams& params) const {
  return request_public(HttpMethod::Get, endpoint("v1", "/constituents"), params);
}

std::string FuturesClient::basis(const QueryParams& params) const {
  return request_public(HttpMethod::Get, "/futures/data/basis", params);
}

std::string FuturesClient::open_interest_history(const QueryParams& params) const {
  return request_public(HttpMethod::Get, "/futures/data/openInterestHist", params);
}

std::string FuturesClient::global_long_short_account_ratio(const QueryParams& params) const {
  return request_public(HttpMethod::Get, "/futures/data/globalLongShortAccountRatio", params);
}

std::string FuturesClient::top_long_short_account_ratio(const QueryParams& params) const {
  return request_public(HttpMethod::Get, "/futures/data/topLongShortAccountRatio", params);
}

std::string FuturesClient::top_long_short_position_ratio(const QueryParams& params) const {
  return request_public(HttpMethod::Get, "/futures/data/topLongShortPositionRatio", params);
}

std::string FuturesClient::taker_buy_sell_volume(const QueryParams& params) const {
  const char* path =
      market_ == FuturesMarket::UsdM ? "/futures/data/takerlongshortRatio" : "/futures/data/takerBuySellVol";
  return request_public(HttpMethod::Get, path, params);
}

}  // namespace binance
