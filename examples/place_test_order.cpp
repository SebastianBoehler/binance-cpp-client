#include <cstdlib>
#include <iostream>

#include "binance/binance.hpp"

int main() {
  const char* key = std::getenv("BINANCE_API_KEY");
  const char* secret = std::getenv("BINANCE_API_SECRET");
  if (key == nullptr || secret == nullptr) {
    std::cerr << "Set BINANCE_API_KEY and BINANCE_API_SECRET\n";
    return 1;
  }

  binance::RestClient client(key, secret);
  binance::OrderRequest order;
  order.symbol = "BTCUSDT";
  order.side = "BUY";
  order.type = "MARKET";
  order.quote_order_qty = "10";

  std::cout << client.test_order(order) << '\n';
  return 0;
}
