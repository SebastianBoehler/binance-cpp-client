# API Coverage

Checked against Binance Spot, USD-M futures, COIN-M futures, Options docs, and
the official Python connector on 2026-06-22.

## Shared Helpers

Each REST client exposes pass-through helpers for routes that are not typed:

- `request_public(method, path, params)`
- `request_api_key(method, path, params)`
- `request_signed(method, path, params)`

## Spot REST

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

## USD-M Futures REST

Typed helpers:

- `GET /fapi/v1/ping`
- `GET /fapi/v1/time`
- `GET /fapi/v1/exchangeInfo`
- `GET /fapi/v1/depth`
- `GET /fapi/v1/trades`
- `GET /fapi/v1/historicalTrades`
- `GET /fapi/v1/aggTrades`
- `GET /fapi/v1/klines`
- `GET /fapi/v1/continuousKlines`
- `GET /fapi/v1/indexPriceKlines`
- `GET /fapi/v1/markPriceKlines`
- `GET /fapi/v1/premiumIndexKlines`
- `GET /fapi/v1/premiumIndex`
- `GET /fapi/v1/fundingRate`
- `GET /fapi/v1/fundingInfo`
- `GET /fapi/v1/ticker/24hr`
- `GET /fapi/v1/ticker/price`
- `GET /fapi/v1/ticker/bookTicker`
- `GET /fapi/v1/openInterest`
- `GET /fapi/v1/constituents`
- `GET /futures/data/basis`
- `GET /futures/data/openInterestHist`
- `GET /futures/data/globalLongShortAccountRatio`
- `GET /futures/data/topLongShortAccountRatio`
- `GET /futures/data/topLongShortPositionRatio`
- `GET /futures/data/takerlongshortRatio`
- `GET /fapi/v3/account`
- `GET /fapi/v3/balance`
- `GET /fapi/v1/positionSide/dual`
- `GET /fapi/v1/income`
- `GET /fapi/v1/leverageBracket`
- `GET /fapi/v1/commissionRate`
- `GET /fapi/v1/rateLimit/order`
- `GET /fapi/v3/positionRisk`
- `GET /fapi/v1/order`
- `GET /fapi/v1/openOrder`
- `GET /fapi/v1/openOrders`
- `GET /fapi/v1/allOrders`
- `GET /fapi/v1/userTrades`
- `GET /fapi/v1/positionMargin/history`
- `GET /fapi/v1/orderAmendment`
- `GET /fapi/v1/forceOrders`
- `GET /fapi/v1/adlQuantile`
- `POST /fapi/v1/order`
- `POST /fapi/v1/order/test`
- `POST /fapi/v1/batchOrders`
- `POST /fapi/v1/positionSide/dual`
- `POST /fapi/v1/leverage`
- `POST /fapi/v1/marginType`
- `POST /fapi/v1/positionMargin`
- `POST /fapi/v1/countdownCancelAll`
- `PUT /fapi/v1/order`
- `PUT /fapi/v1/batchOrders`
- `DELETE /fapi/v1/order`
- `DELETE /fapi/v1/allOpenOrders`
- `DELETE /fapi/v1/batchOrders`

## COIN-M Futures REST

Typed helpers:

- `GET /dapi/v1/ping`
- `GET /dapi/v1/time`
- `GET /dapi/v1/exchangeInfo`
- `GET /dapi/v1/depth`
- `GET /dapi/v1/trades`
- `GET /dapi/v1/historicalTrades`
- `GET /dapi/v1/aggTrades`
- `GET /dapi/v1/klines`
- `GET /dapi/v1/continuousKlines`
- `GET /dapi/v1/indexPriceKlines`
- `GET /dapi/v1/markPriceKlines`
- `GET /dapi/v1/premiumIndexKlines`
- `GET /dapi/v1/premiumIndex`
- `GET /dapi/v1/fundingRate`
- `GET /dapi/v1/fundingInfo`
- `GET /dapi/v1/ticker/24hr`
- `GET /dapi/v1/ticker/price`
- `GET /dapi/v1/ticker/bookTicker`
- `GET /dapi/v1/openInterest`
- `GET /dapi/v1/constituents`
- `GET /futures/data/basis`
- `GET /futures/data/openInterestHist`
- `GET /futures/data/globalLongShortAccountRatio`
- `GET /futures/data/topLongShortAccountRatio`
- `GET /futures/data/topLongShortPositionRatio`
- `GET /futures/data/takerBuySellVol`
- `GET /dapi/v1/account`
- `GET /dapi/v1/balance`
- `GET /dapi/v1/positionSide/dual`
- `GET /dapi/v1/income`
- `GET /dapi/v1/leverageBracket`
- `GET /dapi/v1/commissionRate`
- `GET /dapi/v1/positionRisk`
- `GET /dapi/v1/order`
- `GET /dapi/v1/openOrder`
- `GET /dapi/v1/openOrders`
- `GET /dapi/v1/allOrders`
- `GET /dapi/v1/userTrades`
- `GET /dapi/v1/positionMargin/history`
- `GET /dapi/v1/orderAmendment`
- `GET /dapi/v1/forceOrders`
- `GET /dapi/v1/adlQuantile`
- `POST /dapi/v1/order`
- `POST /dapi/v1/batchOrders`
- `POST /dapi/v1/positionSide/dual`
- `POST /dapi/v1/leverage`
- `POST /dapi/v1/marginType`
- `POST /dapi/v1/positionMargin`
- `POST /dapi/v1/countdownCancelAll`
- `PUT /dapi/v1/order`
- `PUT /dapi/v1/batchOrders`
- `DELETE /dapi/v1/order`
- `DELETE /dapi/v1/allOpenOrders`
- `DELETE /dapi/v1/batchOrders`

## Options REST

Typed helpers:

- `GET /eapi/v1/ping`
- `GET /eapi/v1/time`
- `GET /eapi/v1/exchangeInfo`
- `GET /eapi/v1/exerciseHistory`
- `GET /eapi/v1/index`
- `GET /eapi/v1/klines`
- `GET /eapi/v1/openInterest`
- `GET /eapi/v1/mark`
- `GET /eapi/v1/depth`
- `GET /eapi/v1/blockTrades`
- `GET /eapi/v1/trades`
- `GET /eapi/v1/ticker`
- `GET /eapi/v1/bill`
- `GET /eapi/v1/marginAccount`
- `GET /eapi/v1/userTrades`
- `GET /eapi/v1/position`
- `GET /eapi/v1/openOrders`
- `GET /eapi/v1/historyOrders`
- `GET /eapi/v1/order`
- `GET /eapi/v1/commission`
- `GET /eapi/v1/exerciseRecord`
- `GET /eapi/v1/countdownCancelAll`
- `GET /eapi/v1/mmp`
- `GET /eapi/v1/block/user-trades`
- `GET /eapi/v1/block/order/execute`
- `GET /eapi/v1/block/order/orders`
- `POST /eapi/v1/order`
- `POST /eapi/v1/batchOrders`
- `POST /eapi/v1/countdownCancelAllHeartBeat`
- `POST /eapi/v1/mmpReset`
- `POST /eapi/v1/countdownCancelAll`
- `POST /eapi/v1/mmpSet`
- `POST /eapi/v1/block/order/execute`
- `POST /eapi/v1/block/order/create`
- `PUT /eapi/v1/block/order/create`
- `DELETE /eapi/v1/allOpenOrdersByUnderlying`
- `DELETE /eapi/v1/allOpenOrders`
- `DELETE /eapi/v1/batchOrders`
- `DELETE /eapi/v1/order`
- `DELETE /eapi/v1/block/order/create`

## WebSocket Streams

Typed Spot stream builders:

- `<symbol>@aggTrade`
- `<symbol>@trade`
- `<symbol>@kline_<interval>`
- `<symbol>@ticker`
- `<symbol>@bookTicker`
- `<symbol>@depth`
- `<symbol>@depth@100ms`
- `<symbol>@depth<levels>`
- `<symbol>@depth<levels>@100ms`

Live Spot `SUBSCRIBE` and `UNSUBSCRIBE` control messages are available when
configured with `-DBINANCE_ENABLE_WEBSOCKET=ON`.

## Not Wrapped

- Deprecated Spot listen-key user data stream REST endpoints.
- Deprecated Spot `POST /api/v3/order/oco`; use `POST /api/v3/orderList/oco`.
- Spot, futures, and options WebSocket API request/response methods.
- Futures and options WebSocket stream topic builders.
- Futures portfolio margin, convert, async download, algo-order, and user-data
  listen-key route families.
- Spot margin, Simple Earn, convert, wallet, sub-account, staking, mining, NFT,
  pay, C2C, gift-card, rebate, copy-trading, crypto-loan, VIP-loan, fiat, and
  alpha route families.
- SBE decoding.
