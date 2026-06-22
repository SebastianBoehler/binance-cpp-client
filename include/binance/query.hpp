#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace binance {

using QueryParams = std::vector<std::pair<std::string, std::string>>;

std::string percent_encode(const std::string& input);
std::string encode_query(const QueryParams& params);
bool has_param(const QueryParams& params, const std::string& key);
void append_if(QueryParams& params, const std::string& key, const std::optional<std::string>& value);

}  // namespace binance
