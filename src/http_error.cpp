#include <algorithm>
#include <cctype>
#include <regex>
#include <utility>

#include "binance/http_client.hpp"

namespace binance {
namespace {

std::string lower(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
  return value;
}

std::optional<long> parse_code(const std::string& body) {
  std::smatch match;
  static const std::regex code_regex(R"("code"\s*:\s*(-?\d+))");
  if (std::regex_search(body, match, code_regex)) {
    return std::stol(match[1].str());
  }
  return std::nullopt;
}

std::optional<std::string> parse_message(const std::string& body) {
  std::smatch match;
  static const std::regex msg_regex(R"json("msg"\s*:\s*"([^"]*)")json");
  if (std::regex_search(body, match, msg_regex)) {
    return match[1].str();
  }
  return std::nullopt;
}

}  // namespace

HttpError::HttpError(long status_code, std::string body, HttpHeaders headers)
    : std::runtime_error("Binance HTTP error " + std::to_string(status_code) + ": " + body),
      status_code_(status_code),
      body_(std::move(body)),
      headers_(std::move(headers)),
      api_code_(parse_code(body_)),
      api_message_(parse_message(body_)) {}

std::optional<std::string> HttpError::header(const std::string& name) const {
  const std::string wanted = lower(name);
  for (const auto& [key, value] : headers_) {
    if (lower(key) == wanted) {
      return value;
    }
  }
  return std::nullopt;
}

}  // namespace binance
