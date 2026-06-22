#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <vector>

#ifdef BINANCE_ENABLE_WEBSOCKET
#include <ixwebsocket/IXWebSocket.h>
#endif

namespace binance {

class WebSocketClient {
 public:
  using MessageHandler = std::function<void(const std::string&)>;

  explicit WebSocketClient(std::string url);

  static std::string stream_base_url();
  static std::string market_data_base_url();
  static std::string raw_url(const std::string& stream, const std::string& base_url = stream_base_url());
  static std::string combined_url(const std::vector<std::string>& streams,
                                  const std::string& base_url = stream_base_url());

  static std::string lower_symbol(std::string symbol);
  static std::string aggregate_trade_stream(const std::string& symbol);
  static std::string trade_stream(const std::string& symbol);
  static std::string kline_stream(const std::string& symbol, const std::string& interval);
  static std::string ticker_stream(const std::string& symbol);
  static std::string book_ticker_stream(const std::string& symbol);
  static std::string depth_stream(const std::string& symbol, bool fast = false);
  static std::string partial_depth_stream(const std::string& symbol, int levels, bool fast = false);

  void set_message_handler(MessageHandler handler);
  void connect();
  void close();
  bool is_open() const;
  void subscribe(const std::vector<std::string>& streams, const std::string& id = "");
  void unsubscribe(const std::vector<std::string>& streams, const std::string& id = "");

 private:
  void send_control(const std::string& method, const std::vector<std::string>& streams, const std::string& id);

#ifdef BINANCE_ENABLE_WEBSOCKET
  ix::WebSocket ws_;
#endif
  std::string url_;
  MessageHandler handler_;
  mutable std::mutex mutex_;
};

}  // namespace binance
