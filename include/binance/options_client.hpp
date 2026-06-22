#pragma once

#include <string>

#include "binance/http_client.hpp"
#include "binance/types.hpp"

namespace binance {

class OptionsClient {
 public:
  static constexpr const char* kDefaultBaseUrl = "https://eapi.binance.com";
  static constexpr const char* kTestnetBaseUrl = "https://testnet.binancefuture.com";

  explicit OptionsClient(std::string api_key = "", std::string api_secret = "", std::string base_url = kDefaultBaseUrl,
                         std::string recv_window = "5000", HttpOptions options = {});

  const std::string& base_url() const { return http_.base_url(); }

  std::string warm_up() const;
  std::string request_public(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;
  std::string request_api_key(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;
  std::string request_signed(HttpMethod method, const std::string& path, const QueryParams& params = {}) const;

  std::string ping() const;
  std::string server_time() const;
  std::string exchange_info() const;
  std::string exercise_history(const QueryParams& filters = {}) const;
  std::string index_price(const std::string& underlying) const;
  std::string klines(const std::string& symbol, const std::string& interval, const QueryParams& filters = {}) const;
  std::string open_interest(const QueryParams& params) const;
  std::string mark_price(const QueryParams& filters = {}) const;
  std::string order_book(const std::string& symbol, int limit = 100) const;
  std::string recent_block_trades(const QueryParams& filters = {}) const;
  std::string recent_trades(const std::string& symbol, int limit = 100) const;
  std::string ticker_24hr(const QueryParams& filters = {}) const;

  std::string account_funding_flow(const QueryParams& filters = {}) const;
  std::string margin_account() const;

  std::string account_trades(const QueryParams& filters = {}) const;
  std::string cancel_all_orders(const std::string& symbol) const;
  std::string cancel_all_orders_by_underlying(const std::string& underlying) const;
  std::string cancel_batch_orders(const QueryParams& params) const;
  std::string cancel_order(const QueryParams& params) const;
  std::string new_order(const QueryParams& params) const;
  std::string positions(const QueryParams& filters = {}) const;
  std::string batch_orders(const QueryParams& params) const;
  std::string open_orders(const QueryParams& filters = {}) const;
  std::string history_orders(const QueryParams& filters = {}) const;
  std::string query_order(const QueryParams& params) const;
  std::string commission(const QueryParams& params) const;
  std::string exercise_record(const QueryParams& filters = {}) const;

  std::string countdown_cancel_heartbeat(const QueryParams& params) const;
  std::string get_countdown_cancel_all(const std::string& underlying) const;
  std::string get_mmp_config(const std::string& underlying) const;
  std::string reset_mmp_config(const std::string& underlying) const;
  std::string set_countdown_cancel_all(const QueryParams& params) const;
  std::string set_mmp_config(const QueryParams& params) const;

  std::string execute_block_order(const QueryParams& params) const;
  std::string block_trades(const QueryParams& filters = {}) const;
  std::string cancel_block_order(const QueryParams& params) const;
  std::string extend_block_order(const QueryParams& params) const;
  std::string new_block_order(const QueryParams& params) const;
  std::string query_block_order(const QueryParams& params) const;
  std::string block_orders(const QueryParams& filters = {}) const;

 private:
  static std::string endpoint(const std::string& path);

  HttpClient http_;
};

}  // namespace binance
