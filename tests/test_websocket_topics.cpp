#include <iostream>

#include "binance/websocket_client.hpp"

int main() {
  const auto trade = binance::WebSocketClient::aggregate_trade_stream("BTCUSDT");
  const auto kline = binance::WebSocketClient::kline_stream("ETHUSDT", "1m");
  const auto book = binance::WebSocketClient::book_ticker_stream("BNBUSDT");
  const auto url = binance::WebSocketClient::combined_url({trade, kline, book});

  if (trade != "btcusdt@aggTrade" || kline != "ethusdt@kline_1m" || book != "bnbusdt@bookTicker") {
    std::cerr << "unexpected stream names\n";
    return 1;
  }
  if (url != "wss://stream.binance.com:9443/stream?streams=btcusdt@aggTrade/ethusdt@kline_1m/bnbusdt@bookTicker") {
    std::cerr << "unexpected combined url: " << url << '\n';
    return 1;
  }
  bool rejected_invalid_level = false;
  try {
    (void)binance::WebSocketClient::partial_depth_stream("BTCUSDT", 7);
    std::cerr << "invalid depth level accepted\n";
    return 1;
  } catch (const std::invalid_argument&) {
    rejected_invalid_level = true;
  }
  if (!rejected_invalid_level) {
    std::cerr << "invalid depth level did not throw\n";
    return 1;
  }
  return 0;
}
