#include <iostream>

#include "binance/binance.hpp"

int main() {
  binance::RestClient client;
  std::cout << "Server time: " << client.server_time() << '\n';
  std::cout << "BTCUSDT price: " << client.ticker_price("BTCUSDT") << '\n';
  std::cout << "BTCUSDT book: " << client.book_ticker("BTCUSDT") << '\n';
  return 0;
}
