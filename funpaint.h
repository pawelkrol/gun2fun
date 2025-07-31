#pragma once

#include <optional>
#include <vector>

void append_load_address(std::vector<char>&);

void append_header_info(std::vector<char>&, std::optional<char>);
