#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include "binance/query.hpp"

namespace binance {

enum class HttpMethod : std::uint8_t { Get, Post, Put, Delete };

const char* to_string(HttpMethod method);

struct OrderRequest {
  std::string symbol;
  std::string side;
  std::string type;
  std::optional<std::string> time_in_force;
  std::optional<std::string> quantity;
  std::optional<std::string> quote_order_qty;
  std::optional<std::string> price;
  std::optional<std::string> new_client_order_id;
  std::optional<std::string> new_order_resp_type;
  std::optional<std::string> self_trade_prevention_mode;
  QueryParams extra_params;

  QueryParams params() const;
};

}  // namespace binance
