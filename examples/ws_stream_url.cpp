#include <iostream>

#include "binance/binance.hpp"

int main() {
  const auto url = binance::WebSocketClient::combined_url({
      binance::WebSocketClient::trade_stream("BTCUSDT"),
      binance::WebSocketClient::book_ticker_stream("ETHUSDT"),
  });
  std::cout << url << '\n';
  return 0;
}
