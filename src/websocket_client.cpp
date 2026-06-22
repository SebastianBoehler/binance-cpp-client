#include "binance/websocket_client.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace binance {
namespace {

std::string json_quote(const std::string& value) {
  std::ostringstream out;
  out << '"';
  for (char c : value) {
    if (c == '"' || c == '\\') {
      out << '\\';
    }
    out << c;
  }
  out << '"';
  return out.str();
}

std::string stream_array(const std::vector<std::string>& streams) {
  std::ostringstream out;
  out << '[';
  for (size_t i = 0; i < streams.size(); ++i) {
    out << json_quote(streams[i]);
    if (i + 1 < streams.size()) {
      out << ',';
    }
  }
  out << ']';
  return out.str();
}

std::string control_payload(const std::string& method, const std::vector<std::string>& streams, const std::string& id) {
  std::ostringstream out;
  out << "{\"method\":" << json_quote(method) << ",\"params\":" << stream_array(streams) << ",\"id\":";
  if (id.empty()) {
    out << "null";
  } else {
    out << json_quote(id);
  }
  out << '}';
  return out.str();
}

}  // namespace

WebSocketClient::WebSocketClient(std::string url) : url_(std::move(url)) {}

std::string WebSocketClient::stream_base_url() { return "wss://stream.binance.com:9443"; }

std::string WebSocketClient::market_data_base_url() { return "wss://data-stream.binance.vision"; }

std::string WebSocketClient::raw_url(const std::string& stream, const std::string& base_url) {
  return base_url + "/ws/" + stream;
}

std::string WebSocketClient::combined_url(const std::vector<std::string>& streams, const std::string& base_url) {
  std::ostringstream out;
  out << base_url << "/stream?streams=";
  for (size_t i = 0; i < streams.size(); ++i) {
    out << streams[i];
    if (i + 1 < streams.size()) {
      out << '/';
    }
  }
  return out.str();
}

std::string WebSocketClient::lower_symbol(std::string symbol) {
  std::transform(symbol.begin(), symbol.end(), symbol.begin(),
                 [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
  return symbol;
}

std::string WebSocketClient::aggregate_trade_stream(const std::string& symbol) {
  return lower_symbol(symbol) + "@aggTrade";
}

std::string WebSocketClient::trade_stream(const std::string& symbol) { return lower_symbol(symbol) + "@trade"; }

std::string WebSocketClient::kline_stream(const std::string& symbol, const std::string& interval) {
  return lower_symbol(symbol) + "@kline_" + interval;
}

std::string WebSocketClient::ticker_stream(const std::string& symbol) { return lower_symbol(symbol) + "@ticker"; }

std::string WebSocketClient::book_ticker_stream(const std::string& symbol) {
  return lower_symbol(symbol) + "@bookTicker";
}

std::string WebSocketClient::depth_stream(const std::string& symbol, bool fast) {
  return lower_symbol(symbol) + "@depth" + (fast ? "@100ms" : "");
}

std::string WebSocketClient::partial_depth_stream(const std::string& symbol, int levels, bool fast) {
  if (levels != 5 && levels != 10 && levels != 20) {
    throw std::invalid_argument("Binance partial depth levels must be 5, 10, or 20");
  }
  return lower_symbol(symbol) + "@depth" + std::to_string(levels) + (fast ? "@100ms" : "");
}

void WebSocketClient::set_message_handler(MessageHandler handler) {
  std::lock_guard<std::mutex> lock(mutex_);
  handler_ = std::move(handler);
}

void WebSocketClient::connect() {
#ifdef BINANCE_ENABLE_WEBSOCKET
  ws_.setUrl(url_);
  ws_.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
    if (msg->type == ix::WebSocketMessageType::Message) {
      std::lock_guard<std::mutex> lock(mutex_);
      if (handler_) {
        handler_(msg->str);
      }
    }
  });
  ws_.start();
#else
  throw std::runtime_error("binance_client was built without BINANCE_ENABLE_WEBSOCKET");
#endif
}

void WebSocketClient::close() {
#ifdef BINANCE_ENABLE_WEBSOCKET
  ws_.stop();
#endif
}

bool WebSocketClient::is_open() const {
#ifdef BINANCE_ENABLE_WEBSOCKET
  return ws_.getReadyState() == ix::ReadyState::Open;
#else
  return false;
#endif
}

void WebSocketClient::subscribe(const std::vector<std::string>& streams, const std::string& id) {
  send_control("SUBSCRIBE", streams, id);
}

void WebSocketClient::unsubscribe(const std::vector<std::string>& streams, const std::string& id) {
  send_control("UNSUBSCRIBE", streams, id);
}

void WebSocketClient::send_control(const std::string& method, const std::vector<std::string>& streams,
                                   const std::string& id) {
#ifdef BINANCE_ENABLE_WEBSOCKET
  ws_.send(control_payload(method, streams, id));
#else
  (void)method;
  (void)streams;
  (void)id;
  throw std::runtime_error("binance_client was built without BINANCE_ENABLE_WEBSOCKET");
#endif
}

}  // namespace binance
