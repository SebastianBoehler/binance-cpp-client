# API Coverage

Checked against Binance Spot docs on 2026-06-22.

## REST

Typed helpers:

- `GET /api/v3/ping`
- `GET /api/v3/time`
- `GET /api/v3/exchangeInfo`
- `GET /api/v3/executionRules`
- `GET /api/v3/depth`
- `GET /api/v3/trades`
- `GET /api/v3/historicalTrades`
- `GET /api/v3/historicalBlockTrades`
- `GET /api/v3/aggTrades`
- `GET /api/v3/klines`
- `GET /api/v3/uiKlines`
- `GET /api/v3/avgPrice`
- `GET /api/v3/referencePrice`
- `GET /api/v3/referencePrice/calculation`
- `GET /api/v3/ticker`
- `GET /api/v3/ticker/24hr`
- `GET /api/v3/ticker/price`
- `GET /api/v3/ticker/bookTicker`
- `GET /api/v3/ticker/tradingDay`
- `GET /api/v3/account`
- `GET /api/v3/account/commission`
- `GET /api/v3/order`
- `GET /api/v3/openOrders`
- `GET /api/v3/allOrders`
- `GET /api/v3/myTrades`
- `GET /api/v3/orderList`
- `GET /api/v3/openOrderList`
- `GET /api/v3/allOrderList`
- `GET /api/v3/myAllocations`
- `GET /api/v3/myFilters`
- `GET /api/v3/myPreventedMatches`
- `GET /api/v3/order/amendments`
- `GET /api/v3/rateLimit/order`
- `POST /api/v3/order`
- `POST /api/v3/order/test`
- `POST /api/v3/order/cancelReplace`
- `POST /api/v3/orderList/oco`
- `POST /api/v3/orderList/oto`
- `POST /api/v3/orderList/otoco`
- `POST /api/v3/orderList/opo`
- `POST /api/v3/orderList/opoco`
- `POST /api/v3/sor/order`
- `POST /api/v3/sor/order/test`
- `PUT /api/v3/order/amend/keepPriority`
- `DELETE /api/v3/order`
- `DELETE /api/v3/openOrders`
- `DELETE /api/v3/orderList`

This now matches the current official Spot connector's current REST account and
trade route families except the deprecated `POST /api/v3/order/oco`.

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
- Deprecated `POST /api/v3/order/oco`; use `POST /api/v3/orderList/oco`.
- WebSocket API request/response methods.
- Margin, futures, options, Simple Earn, convert, and wallet routes.
- SBE decoding.
