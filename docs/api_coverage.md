# API Coverage

Checked against Binance Spot docs on 2026-06-22.

## REST

Typed helpers:

- `GET /api/v3/ping`
- `GET /api/v3/time`
- `GET /api/v3/exchangeInfo`
- `GET /api/v3/depth`
- `GET /api/v3/trades`
- `GET /api/v3/aggTrades`
- `GET /api/v3/klines`
- `GET /api/v3/avgPrice`
- `GET /api/v3/ticker/price`
- `GET /api/v3/ticker/bookTicker`
- `GET /api/v3/account`
- `GET /api/v3/order`
- `GET /api/v3/openOrders`
- `GET /api/v3/allOrders`
- `GET /api/v3/myTrades`
- `POST /api/v3/order`
- `POST /api/v3/order/test`
- `DELETE /api/v3/order`
- `DELETE /api/v3/openOrders`

Generic helpers:

- `request_public(method, path, params)`
- `request_api_key(method, path, params)`
- `request_signed(method, path, params)`

## WebSocket Streams

Typed stream builders:

- `<symbol>@aggTrade`
- `<symbol>@trade`
- `<symbol>@kline_<interval>`
- `<symbol>@ticker`
- `<symbol>@bookTicker`
- `<symbol>@depth`
- `<symbol>@depth@100ms`
- `<symbol>@depth<levels>`
- `<symbol>@depth<levels>@100ms`

Live `SUBSCRIBE` and `UNSUBSCRIBE` control messages are available when
configured with `-DBINANCE_ENABLE_WEBSOCKET=ON`.

## Not Wrapped

- Deprecated listen-key user data stream REST endpoints.
- WebSocket API request/response methods.
- Margin, futures, options, Simple Earn, convert, and wallet routes.
- SBE decoding.

