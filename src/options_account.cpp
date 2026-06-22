#include "binance/options_client.hpp"

namespace binance {

std::string OptionsClient::account_funding_flow(const QueryParams& filters) const {
  return request_signed(HttpMethod::Get, endpoint("/bill"), filters);
}

std::string OptionsClient::margin_account() const {
  return request_signed(HttpMethod::Get, endpoint("/marginAccount"));
}

}  // namespace binance
