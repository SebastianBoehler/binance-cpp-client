#include <iostream>

#include "binance/types.hpp"

int main() {
  binance::OrderRequest request;
  request.symbol = "BTCUSDT";
  request.side = "BUY";
  request.type = "LIMIT";
  request.time_in_force = "GTC";
  request.quantity = "0.01";
  request.price = "10000";
  request.new_client_order_id = "client-1";
  request.extra_params.emplace_back("strategyType", "1000000");

  const std::string query = binance::encode_query(request.params());
  const std::string expected =
      "symbol=BTCUSDT&side=BUY&type=LIMIT&timeInForce=GTC&quantity=0.01&price=10000&newClientOrderId=client-1&"
      "strategyType=1000000";
  if (query != expected) {
    std::cerr << "unexpected order params: " << query << '\n';
    return 1;
  }
  return 0;
}
