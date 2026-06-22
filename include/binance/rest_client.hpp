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
  std::string order_book(const std::string& symbol, int limit = 100) const;
  std::string recent_trades(const std::string& symbol, int limit = 500) const;
  std::string aggregate_trades(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string klines(const std::string& symbol, const std::string& interval, const QueryParams& filters = {}) const;
  std::string average_price(const std::string& symbol) const;
  std::string ticker_price(const std::optional<std::string>& symbol = std::nullopt) const;
  std::string book_ticker(const std::optional<std::string>& symbol = std::nullopt) const;

  std::string account_info(const std::optional<std::string>& omit_zero_balances = std::nullopt) const;
  std::string query_order(const std::string& symbol, const QueryParams& ids) const;
  std::string open_orders(const std::optional<std::string>& symbol = std::nullopt) const;
  std::string all_orders(const std::string& symbol, const QueryParams& filters = {}) const;
  std::string account_trades(const std::string& symbol, const QueryParams& filters = {}) const;

  std::string new_order(const OrderRequest& request) const;
  std::string test_order(const OrderRequest& request) const;
  std::string cancel_order(const std::string& symbol, const QueryParams& ids) const;
  std::string cancel_open_orders(const std::string& symbol) const;

 private:
  HttpClient http_;
};

}  // namespace binance
