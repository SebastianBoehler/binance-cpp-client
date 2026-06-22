#pragma once

#include <optional>
#include <string>

#include "binance/http_client.hpp"
#include "binance/types.hpp"

namespace binance {

class RestClient {
 public:
  static constexpr const char* kDefaultBaseUrl = "https://api.binance.com";
  static constexpr const char* kTestnetBaseUrl = "https://testnet.binance.vision";

  explicit RestClient(std::string api_key = "", std::string api_secret = "", std::string base_url = kDefaultBaseUrl,
                      std::string recv_window = "5000", HttpOptions options = {});

  std::string warm_up() const;
  std::string request_public(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;
  std::string request_api_key(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;
  std::string request_signed(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;

  std::string ping() const;
  std::string server_time() const;
  std::string exchange_info(const QueryParams& filters = {}) const;
  std::string execution_rules(const QueryParams& filters = {}) const;
  std::string order_book(const std::string& symbol, int limit = 100) const;
  std::string recent_trades(const std::string& symbol, int limit = 500) const;
  std::string historical_trades(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string historical_block_trades(const std::string& symbol, const std::string& from_id,
                                      const QueryParams& filters = {}) const;
  std::string aggregate_trades(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string klines(const std::string& symbol, const std::string& interval, const QueryParams& filters = {}) const;
  std::string ui_klines(const std::string& symbol, const std::string& interval, const QueryParams& filters = {}) const;
  std::string average_price(const std::string& symbol) const;
  std::string reference_price(const std::string& symbol) const;
  std::string reference_price_calculation(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string rolling_ticker(const QueryParams& filters = {}) const;
  std::string ticker_24hr(const QueryParams& filters = {}) const;
  std::string trading_day_ticker(const QueryParams& filters = {}) const;
  std::string ticker_price(const std::optional<std::string>& symbol = std::nullopt) const;
  std::string ticker_price(const QueryParams& filters) const;
  std::string book_ticker(const std::optional<std::string>& symbol = std::nullopt) const;
  std::string book_ticker(const QueryParams& filters) const;

  std::string account_info(const std::optional<std::string>& omit_zero_balances = std::nullopt) const;
  std::string account_commission(const std::string& symbol) const;
  std::string query_order(const std::string& symbol, const QueryParams& ids) const;
  std::string open_orders(const std::optional<std::string>& symbol = std::nullopt) const;
  std::string all_orders(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string account_trades(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string order_list(const QueryParams& ids) const;
  std::string open_order_lists() const;
  std::string all_order_lists(const QueryParams& filters = {}) const;
  std::string account_allocations(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string account_filters(const std::string& symbol) const;
  std::string prevented_matches(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string order_amendments(const std::string& symbol, const std::string& order_id,
                               const QueryParams& filters = {}) const;
  std::string order_rate_limit() const;

  std::string new_order(const OrderRequest& request) const;
  std::string test_order(const OrderRequest& request) const;
  std::string cancel_order(const std::string& symbol, const QueryParams& ids) const;
  std::string cancel_open_orders(const std::string& symbol) const;
  std::string cancel_order_list(const std::string& symbol, const QueryParams& ids) const;
  std::string amend_order_keep_priority(const std::string& symbol, const std::string& new_qty,
                                        const QueryParams& ids = {}) const;
  std::string cancel_replace_order(const QueryParams& params) const;
  std::string order_list_oco(const QueryParams& params) const;
  std::string order_list_oto(const QueryParams& params) const;
  std::string order_list_otoco(const QueryParams& params) const;
  std::string order_list_opo(const QueryParams& params) const;
  std::string order_list_opoco(const QueryParams& params) const;
  std::string sor_order(const QueryParams& params) const;
  std::string sor_test_order(const QueryParams& params) const;

 private:
  HttpClient http_;
};

}  // namespace binance
