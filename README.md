# Binance C++ Client

Small C++20 Binance client with Spot, USD-M futures, COIN-M futures, and Options
REST coverage in the same practical shape as `bybit-cpp-client`: reusable HTTP
transport, HMAC signing, raw JSON responses, thin typed route helpers, and
pass-through methods for unwrapped endpoints.

## C++ Exchange Client Suite

This repository is part of a small C++ crypto exchange client suite:

- [binance-cpp-client](https://github.com/SebastianBoehler/binance-cpp-client)
  for Binance Spot, USD-M futures, COIN-M futures, and Options REST plus Spot
  public market WebSocket helpers.
- [bybit-cpp-client](https://github.com/SebastianBoehler/bybit-cpp-client)
  for Bybit Open API V5 REST, optional WebSockets, and SBE helpers.

Both clients favor reusable transports, OpenSSL signing, raw upstream JSON, and
thin route wrappers so trading systems can share the same integration style
across exchanges without inheriting hidden strategy logic.

## Scope

- Spot REST base URL: `https://api.binance.com`
- Spot testnet base URL: `https://testnet.binance.vision`
- USD-M futures REST base URL: `https://fapi.binance.com`
- USD-M futures testnet base URL: `https://demo-fapi.binance.com`
- COIN-M futures REST base URL: `https://dapi.binance.com`
- COIN-M futures testnet base URL: `https://testnet.binancefuture.com`
- Options REST base URL: `https://eapi.binance.com`
- Options testnet base URL: `https://testnet.binancefuture.com`
- Spot public market endpoints: ping, time, exchange info, depth, trades,
  aggregate trades, historical trades, klines, average price, reference price,
  execution rules, ticker families, and book ticker.
- Spot signed account/trading endpoints: account info, order lookup, open
  orders, all orders, account trades, commissions, order lists, allocations, STP
  prevented matches, amendments, rate-limit usage, order placement, test order,
  cancellation, cancel-replace, amend-keep-priority, order-list placement, and
  SOR placement.
- Futures public market endpoints: exchange info, depth, trades, aggregate
  trades, klines, continuous/index/mark/premium index klines, mark price,
  funding rates, funding info, tickers, open interest, constituents, basis,
  long/short ratios, and taker buy/sell volume.
- Futures signed account/trading endpoints: account info, balance, position
  mode, position risk, income history, leverage brackets, commission rate, order
  placement, USD-M test order, order lookup, open/all orders, batch orders,
  modification, cancellation, position margin, leverage/margin-type changes,
  ADL quantile, force orders, and countdown cancel-all.
- Options public market endpoints: exchange info, exercise history, index
  price, klines, open interest, mark price, depth, trades, block trades, and
  ticker.
- Options signed account/trading endpoints: margin account, funding flow, order
  placement, lookup, history, cancellation, batch orders, open orders,
  positions, trades, commission, exercise records, market-maker protection, and
  block-trade flows.
- Public market WebSocket stream URL/topic helpers, with an optional live
  `ixwebsocket` implementation for Spot streams.
- Generic `request_public`, `request_api_key`, and `request_signed` helpers for
  routes that are not yet typed.

Current Binance references checked on 2026-06-22:

- [General REST API information](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/general-api-information)
- [Request security](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/request-security)
- [Market data endpoints](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/market-data-endpoints)
- [Trading endpoints](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/trading-endpoints)
- [Account endpoints](https://developers.binance.com/docs/binance-spot-api-docs/rest-api/account-endpoints)
- [WebSocket streams](https://developers.binance.com/docs/binance-spot-api-docs/web-socket-streams)
- [USD-M Futures general information](https://developers.binance.com/docs/derivatives/usds-margined-futures/general-info)
- [COIN-M Futures general information](https://developers.binance.com/docs/derivatives/coin-margined-futures/general-info)
- [Options general information](https://developers.binance.com/docs/derivatives/options-trading/general-info)
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

USD-M futures public market snapshot:

```cpp
binance::FuturesClient futures(binance::FuturesMarket::UsdM);
std::cout << futures.ticker_price({{"symbol", "BTCUSDT"}}) << '\n';
```

Options public market data:

```cpp
binance::OptionsClient options;
std::cout << options.exchange_info() << '\n';
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
