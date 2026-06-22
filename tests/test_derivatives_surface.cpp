#include <cassert>
#include <string>

#include "binance/binance.hpp"

int main() {
  using Futures = binance::FuturesClient;
  using Options = binance::OptionsClient;
  using Params = binance::QueryParams;

  Futures usdm(binance::FuturesMarket::UsdM);
  Futures coinm(binance::FuturesMarket::CoinM);
  Options options("", "", "https://example.test");

  assert(usdm.base_url() == Futures::kUsdMBaseUrl);
  assert(coinm.base_url() == Futures::kCoinMBaseUrl);
  assert(options.base_url() == "https://example.test");

  auto futures_book = static_cast<std::string (Futures::*)(const std::string&, int) const>(&Futures::order_book);
  auto futures_klines =
      static_cast<std::string (Futures::*)(const std::string&, const std::string&, const Params&) const>(
          &Futures::klines);
  auto futures_stats = static_cast<std::string (Futures::*)(const Params&) const>(&Futures::open_interest_history);
  auto futures_account = static_cast<std::string (Futures::*)() const>(&Futures::account_info);
  auto futures_position = static_cast<std::string (Futures::*)(const Params&) const>(&Futures::position_risk);
  auto futures_new_order = static_cast<std::string (Futures::*)(const Params&) const>(&Futures::new_order);
  auto futures_modify = static_cast<std::string (Futures::*)(const Params&) const>(&Futures::modify_order);
  auto futures_leverage =
      static_cast<std::string (Futures::*)(const std::string&, int) const>(&Futures::change_leverage);

  auto options_book = static_cast<std::string (Options::*)(const std::string&, int) const>(&Options::order_book);
  auto options_klines =
      static_cast<std::string (Options::*)(const std::string&, const std::string&, const Params&) const>(
          &Options::klines);
  auto options_account = static_cast<std::string (Options::*)() const>(&Options::margin_account);
  auto options_positions = static_cast<std::string (Options::*)(const Params&) const>(&Options::positions);
  auto options_order = static_cast<std::string (Options::*)(const Params&) const>(&Options::new_order);
  auto options_mmp = static_cast<std::string (Options::*)(const Params&) const>(&Options::set_mmp_config);
  auto options_block = static_cast<std::string (Options::*)(const Params&) const>(&Options::new_block_order);

  (void)futures_book;
  (void)futures_klines;
  (void)futures_stats;
  (void)futures_account;
  (void)futures_position;
  (void)futures_new_order;
  (void)futures_modify;
  (void)futures_leverage;
  (void)options_book;
  (void)options_klines;
  (void)options_account;
  (void)options_positions;
  (void)options_order;
  (void)options_mmp;
  (void)options_block;

  return 0;
}
