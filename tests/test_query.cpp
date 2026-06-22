#include <iostream>

#include "binance/query.hpp"

int main() {
  const std::string encoded = binance::percent_encode("alpha & １２");
  if (encoded != "alpha%20%26%20%EF%BC%91%EF%BC%92") {
    std::cerr << "unexpected percent encoding: " << encoded << '\n';
    return 1;
  }

  const std::string query = binance::encode_query({{"b", "2"}, {"a", "1"}});
  if (query != "b=2&a=1") {
    std::cerr << "query order changed: " << query << '\n';
    return 1;
  }

  if (!binance::has_param({{"symbol", "BTCUSDT"}}, "symbol")) {
    std::cerr << "expected symbol param\n";
    return 1;
  }
  return 0;
}
