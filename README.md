# Binance C++ Client

Small C++20 Binance Spot client with the same practical shape as
`bybit-cpp-client`: reusable HTTP transport, HMAC signing, raw JSON responses,
thin typed route helpers, and pass-through methods for unwrapped endpoints.

## C++ Exchange Client Suite

This repository is part of a small C++ crypto exchange client suite:

- [binance-cpp-client](https://github.com/SebastianBoehler/binance-cpp-client)
  for Binance Spot REST and public market WebSocket helpers.
- [bybit-cpp-client](https://github.com/SebastianBoehler/bybit-cpp-client)
  for Bybit Open API V5 REST, optional WebSockets, and SBE helpers.

Both clients favor reusable transports, OpenSSL signing, raw upstream JSON, and
thin route wrappers so trading systems can share the same integration style
across exchanges without inheriting hidden strategy logic.

## Scope

- Spot REST base URL: `https://api.binance.com`
- Spot testnet base URL: `https://testnet.binance.vision`
- Public market endpoints: ping, time, exchange info, depth, trades, aggregate
  trades, historical trades, klines, average price, reference price, execution
  rules, ticker families, and book ticker.
- Signed account/trading endpoints: account info, order lookup, open orders,
  all orders, account trades, commissions, order lists, allocations, STP
  prevented matches, amendments, rate-limit usage, order placement, test order,
  cancellation, cancel-replace, amend-keep-priority, order-list placement, and
  SOR placement.
- Public market WebSocket stream URL/topic helpers, with an optional live
  `ixwebsocket` implementation.
- Generic `request_public`, `request_api_key`, and `request_signed` helpers for
  routes that are not yet typed.

Current Binance references checked on 2026-06-22:

- [General REST API information](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/general-api-information)
- [Request security](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/request-security)
- [Market data endpoints](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/market-data-endpoints)
- [Trading endpoints](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/trading-endpoints)
- [Account endpoints](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/account-endpoints)
- [WebSocket streams](https://developers.binance.com/docs/binance-spot-api-docs/web-socket-streams)
- [Official Python connector](https://github.com/binance/binance-connector-python)

The old REST listen-key user data stream endpoints are intentionally not wrapped;
current docs point user data subscriptions at the WebSocket API instead.

## Build

```sh
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
```

Enable the live WebSocket implementation when needed:

```sh
cmake -S . -B build-ws -G Ninja -DBINANCE_ENABLE_WEBSOCKET=ON
cmake --build build-ws
```

## Usage

```cpp
#include <iostream>
#include "binance/binance.hpp"

int main() {
  binance::RestClient client;
  std::cout << client.ticker_price("BTCUSDT") << '\n';
}
```

Signed test order:

```cpp
binance::RestClient client(api_key, api_secret);
binance::OrderRequest order;
order.symbol = "BTCUSDT";
order.side = "BUY";
order.type = "MARKET";
order.quote_order_qty = "10";
client.test_order(order);
```

Public combined stream URL:

```cpp
auto url = binance::WebSocketClient::combined_url({
    binance::WebSocketClient::trade_stream("BTCUSDT"),
    binance::WebSocketClient::book_ticker_stream("ETHUSDT"),
});
```

## Design Notes

- One `CURL*` easy handle is reused per `HttpClient`, guarded by a mutex.
- libcurl DNS and TLS session caches are shared across clients by default.
- TCP keepalive and `TCP_NODELAY` are enabled by default for lower request
  latency.
- Signed requests percent-encode parameters first, then compute HMAC SHA-256
  over the exact query string that is sent.
- Parameters are not sorted; insertion order is preserved so callers can reason
  about the signed payload.
- HTTP status errors throw `binance::HttpError` and expose response headers,
  raw body, and parsed Binance `code`/`msg` when present.
