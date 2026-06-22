#include <iostream>

#include "binance/query.hpp"
#include "binance/signing.hpp"

int main() {
  const std::string secret = "NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j";
  const binance::QueryParams params{
      {"symbol", "LTCBTC"}, {"side", "BUY"},  {"type", "LIMIT"},      {"timeInForce", "GTC"},
      {"quantity", "1"},    {"price", "0.1"}, {"recvWindow", "5000"}, {"timestamp", "1499827319559"}};
  const std::string query = binance::encode_query(params);
  const std::string signature = binance::Signer::sign_query(secret, query);
  const std::string expected = "c8db56825ae71d6d79447849e617115f4a920fa2acdcab2b053c4b2838bd6b71";

  if (query !=
      "symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=0.1&recvWindow=5000&"
      "timestamp=1499827319559") {
    std::cerr << "unexpected query: " << query << '\n';
    return 1;
  }
  if (signature != expected) {
    std::cerr << "unexpected signature: " << signature << '\n';
    return 1;
  }
  return 0;
}
