#include <iostream>

#include "binance/binance.hpp"

int main() {
  binance::FuturesClient client(binance::FuturesMarket::UsdM);

  std::cout << client.server_time() << '\n';
  std::cout << client.ticker_price({{"symbol", "BTCUSDT"}}) << '\n';
}
