#include "funpaint.h"

#include <algorithm>
#include <optional>
#include <vector>

void append_load_address(std::vector<char>& data) {
  // Load address: 0x3ff0
  static const std::vector<char8_t> load_address = { 0xf0, 0x3f };
  std::copy(load_address.begin(), load_address.end(), data.begin() + 0x0000);
}

void append_header_info(std::vector<char>& data, std::optional<char> escape) {
  // Header info: 0x3ff0..0x3fff ("funpaint (mt) ")
  static const std::vector<char8_t> header_info = { 0x46, 0x55, 0x4e, 0x50, 0x41, 0x49, 0x4e, 0x54, 0x20, 0x28, 0x4d, 0x54, 0x29, 0x20 };
  std::copy(header_info.begin(), header_info.end(), data.begin() + 0x0002);

  std::vector<char8_t> rle_info = { 0x00, 0x00 };
  if (escape.has_value()) {
    rle_info = { 0x01, static_cast<char8_t>(escape.value()) };
  }
  std::copy(rle_info.begin(), rle_info.end(), data.begin() + 0x0010);
}
