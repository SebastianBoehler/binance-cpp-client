#include "binance/signing.hpp"

#include <openssl/core_names.h>
#include <openssl/evp.h>
#include <openssl/params.h>

#include <chrono>
#include <iomanip>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace binance {
namespace {

struct EvpMacDeleter {
  void operator()(EVP_MAC* mac) const { EVP_MAC_free(mac); }
};

struct EvpMacCtxDeleter {
  void operator()(EVP_MAC_CTX* ctx) const { EVP_MAC_CTX_free(ctx); }
};

}  // namespace

std::int64_t Signer::now_ms() {
  const auto now = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

std::string Signer::hmac_sha256_hex(const std::string& key, const std::string& payload) {
  std::unique_ptr<EVP_MAC, EvpMacDeleter> mac(EVP_MAC_fetch(nullptr, "HMAC", nullptr));
  if (!mac) {
    throw std::runtime_error("EVP_MAC_fetch(HMAC) failed");
  }

  std::unique_ptr<EVP_MAC_CTX, EvpMacCtxDeleter> ctx(EVP_MAC_CTX_new(mac.get()));
  if (!ctx) {
    throw std::runtime_error("EVP_MAC_CTX_new failed");
  }

  char digest[] = "SHA256";
  OSSL_PARAM params[] = {OSSL_PARAM_construct_utf8_string(OSSL_MAC_PARAM_DIGEST, digest, 0),
                         OSSL_PARAM_construct_end()};

  const auto* key_bytes = reinterpret_cast<const unsigned char*>(key.data());
  if (EVP_MAC_init(ctx.get(), key_bytes, key.size(), params) != 1) {
    throw std::runtime_error("EVP_MAC_init failed");
  }

  const auto* payload_bytes = reinterpret_cast<const unsigned char*>(payload.data());
  if (EVP_MAC_update(ctx.get(), payload_bytes, payload.size()) != 1) {
    throw std::runtime_error("EVP_MAC_update failed");
  }

  unsigned char hash[EVP_MAX_MD_SIZE];
  size_t hash_len = 0;
  if (EVP_MAC_final(ctx.get(), hash, &hash_len, sizeof(hash)) != 1) {
    throw std::runtime_error("EVP_MAC_final failed");
  }

  std::ostringstream out;
  for (size_t i = 0; i < hash_len; ++i) {
    out << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
  }
  return out.str();
}

std::string Signer::sign_query(const std::string& secret_key, const std::string& encoded_query) {
  return hmac_sha256_hex(secret_key, encoded_query);
}

}  // namespace binance
