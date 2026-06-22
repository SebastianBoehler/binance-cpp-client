#include <iostream>

#include "binance/binance.hpp"

int main() {
  binance::OptionsClient client;

  std::cout << client.server_time() << '\n';
  std::cout << client.ticker_24hr({{"underlying", "BTCUSDT"}}) << '\n';
}
