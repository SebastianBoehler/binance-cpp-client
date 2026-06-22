#pragma once

#include <cstdint>
#include <string>

#include "binance/http_client.hpp"
#include "binance/types.hpp"

namespace binance {

enum class FuturesMarket : std::uint8_t { UsdM, CoinM };

class FuturesClient {
 public:
  static constexpr const char* kUsdMBaseUrl = "https://fapi.binance.com";
  static constexpr const char* kUsdMTestnetBaseUrl = "https://demo-fapi.binance.com";
  static constexpr const char* kCoinMBaseUrl = "https://dapi.binance.com";
  static constexpr const char* kCoinMTestnetBaseUrl = "https://testnet.binancefuture.com";

  explicit FuturesClient(FuturesMarket market, std::string api_key = "", std::string api_secret = "",
                         std::string base_url = "", std::string recv_window = "5000", HttpOptions options = {});

  FuturesMarket market() const { return market_; }
  const std::string& base_url() const { return http_.base_url(); }

  std::string warm_up() const;
  std::string request_public(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;
  std::string request_api_key(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;
  std::string request_signed(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;

  std::string ping() const;
  std::string server_time() const;
  std::string exchange_info() const;
  std::string order_book(const std::string& symbol, int limit = 100) const;
  std::string recent_trades(const std::string& symbol, int limit = 500) const;
  std::string historical_trades(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string aggregate_trades(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string klines(const std::string& symbol, const std::string& interval, const QueryParams& filters = {}) const;
  std::string continuous_klines(const std::string& pair, const std::string& contract_type, const std::string& interval,
                                const QueryParams& filters = {}) const;
  std::string index_price_klines(const std::string& pair, const std::string& interval,
                                 const QueryParams& filters = {}) const;
  std::string mark_price_klines(const std::string& symbol, const std::string& interval,
                                const QueryParams& filters = {}) const;
  std::string premium_index_klines(const QueryParams& params) const;
  std::string mark_price(const QueryParams& filters = {}) const;
  std::string funding_rate(const QueryParams& filters = {}) const;
  std::string funding_info() const;
  std::string ticker_24hr(const QueryParams& filters = {}) const;
  std::string ticker_price(const QueryParams& filters = {}) const;
  std::string book_ticker(const QueryParams& filters = {}) const;
  std::string open_interest(const std::string& symbol) const;
  std::string constituents(const QueryParams& params) const;
  std::string basis(const QueryParams& params) const;
  std::string open_interest_history(const QueryParams& params) const;
  std::string global_long_short_account_ratio(const QueryParams& params) const;
  std::string top_long_short_account_ratio(const QueryParams& params) const;
  std::string top_long_short_position_ratio(const QueryParams& params) const;
  std::string taker_buy_sell_volume(const QueryParams& params) const;

  std::string account_info() const;
  std::string account_balance() const;
  std::string position_mode() const;
  std::string income_history(const QueryParams& filters = {}) const;
  std::string leverage_bracket(const QueryParams& filters = {}) const;
  std::string commission_rate(const std::string& symbol) const;
  std::string order_rate_limit() const;
  std::string position_risk(const QueryParams& filters = {}) const;

  std::string new_order(const QueryParams& params) const;
  std::string usdm_test_order(const QueryParams& params) const;
  std::string query_order(const QueryParams& params) const;
  std::string cancel_order(const QueryParams& params) const;
  std::string cancel_all_open_orders(const std::string& symbol) const;
  std::string batch_orders(const QueryParams& params) const;
  std::string cancel_batch_orders(const QueryParams& params) const;
  std::string modify_order(const QueryParams& params) const;
  std::string modify_batch_orders(const QueryParams& params) const;
  std::string open_order(const QueryParams& params) const;
  std::string open_orders(const QueryParams& filters = {}) const;
  std::string all_orders(const QueryParams& params) const;
  std::string account_trades(const QueryParams& params) const;
  std::string change_position_mode(bool dual_side_position) const;
  std::string change_leverage(const std::string& symbol, int leverage) const;
  std::string change_margin_type(const std::string& symbol, const std::string& margin_type) const;
  std::string modify_position_margin(const QueryParams& params) const;
  std::string position_margin_history(const QueryParams& params) const;
  std::string order_modify_history(const QueryParams& params) const;
  std::string countdown_cancel_all(const QueryParams& params) const;
  std::string force_orders(const QueryParams& filters = {}) const;
  std::string adl_quantile(const QueryParams& filters = {}) const;

 private:
  std::string endpoint(const std::string& version, const std::string& path) const;
  std::string account_endpoint(const std::string& usdm_path, const std::string& coinm_path) const;
  void require_usdm(const std::string& method) const;

  FuturesMarket market_;
  std::string prefix_;
  HttpClient http_;
};

}  // namespace binance
