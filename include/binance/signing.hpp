#pragma once

#include <cstdint>
#include <string>

namespace binance {

class Signer {
 public:
  static std::int64_t now_ms();
  static std::string hmac_sha256_hex(const std::string& key, const std::string& payload);
  static std::string sign_query(const std::string& secret_key, const std::string& encoded_query);
};

}  // namespace binance
