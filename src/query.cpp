#include "binance/query.hpp"

#include <cctype>
#include <iomanip>
#include <sstream>

namespace binance {
namespace {

bool is_unreserved(unsigned char c) { return std::isalnum(c) != 0 || c == '-' || c == '.' || c == '_' || c == '~'; }

}  // namespace

std::string percent_encode(const std::string& input) {
  std::ostringstream out;
  out << std::uppercase << std::hex;
  for (unsigned char c : input) {
    if (is_unreserved(c)) {
      out << c;
    } else {
      out << '%' << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
  }
  return out.str();
}

std::string encode_query(const QueryParams& params) {
  std::ostringstream out;
  for (size_t i = 0; i < params.size(); ++i) {
    out << percent_encode(params[i].first) << '=' << percent_encode(params[i].second);
    if (i + 1 < params.size()) {
      out << '&';
    }
  }
  return out.str();
}

bool has_param(const QueryParams& params, const std::string& key) {
  for (const auto& kv : params) {
    if (kv.first == key) {
      return true;
    }
  }
  return false;
}

void append_if(QueryParams& params, const std::string& key, const std::optional<std::string>& value) {
  if (value.has_value() && !value->empty()) {
    params.emplace_back(key, *value);
  }
}

}  // namespace binance
