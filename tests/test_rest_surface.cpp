#include <string>

#include "binance/rest_client.hpp"

int main() {
  using Client = binance::RestClient;
  using Params = binance::QueryParams;

  auto public_filters = static_cast<std::string (Client::*)(const Params&) const>(&Client::execution_rules);
  auto price_filters = static_cast<std::string (Client::*)(const Params&) const>(&Client::ticker_price);
  auto book_filters = static_cast<std::string (Client::*)(const Params&) const>(&Client::book_ticker);

  auto commission = static_cast<std::string (Client::*)(const std::string&) const>(&Client::account_commission);
  auto order_lists = static_cast<std::string (Client::*)(const Params&) const>(&Client::all_order_lists);
  auto rate_limit = static_cast<std::string (Client::*)() const>(&Client::order_rate_limit);

  auto cancel_replace = static_cast<std::string (Client::*)(const Params&) const>(&Client::cancel_replace_order);
  auto list_oco = static_cast<std::string (Client::*)(const Params&) const>(&Client::order_list_oco);
  auto list_oto = static_cast<std::string (Client::*)(const Params&) const>(&Client::order_list_oto);
  auto list_otoco = static_cast<std::string (Client::*)(const Params&) const>(&Client::order_list_otoco);
  auto list_opo = static_cast<std::string (Client::*)(const Params&) const>(&Client::order_list_opo);
  auto list_opoco = static_cast<std::string (Client::*)(const Params&) const>(&Client::order_list_opoco);

  (void)public_filters;
  (void)price_filters;
  (void)book_filters;
  (void)commission;
  (void)order_lists;
  (void)rate_limit;
  (void)cancel_replace;
  (void)list_oco;
  (void)list_oto;
  (void)list_otoco;
  (void)list_opo;
  (void)list_opoco;
  return 0;
}
