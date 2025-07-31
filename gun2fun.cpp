#include "gun2fun.h"

#include "fileutils.h"
#include "funpaint.h"
#include "memory.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

void validate_input(const std::vector<char>& gunpaint) {
  // Load address: 0x4000
  static const std::vector<char8_t> load_address = { 0x00, 0x40 };
  if (!std::equal(load_address.begin(), load_address.end(), gunpaint.begin() + 0x0000)) {
    fail(std::string("Invalid input file: load address must be $4000"));
  }

  // Header info: 0x43e8..0x43f7 ("gunpaint (jz)   ")
  static const std::vector<char8_t> header_info = { 0x47, 0x55, 0x4e, 0x50, 0x41, 0x49, 0x4e, 0x54, 0x20, 0x28, 0x4a, 0x5a, 0x29, 0x20, 0x20, 0x20 };
  if (!std::equal(header_info.begin(), header_info.end(), gunpaint.begin() + 0x03ea)) {
    fail(std::string("Invalid input file: missing Gunpaint header"));
  }
}

std::vector<char> convert_data(const std::vector<char>& gunpaint) {
  validate_input(gunpaint);
  std::size_t size = 33694;
  std::vector<char> data(size);

  // Load address: 0x3ff0
  append_load_address(data);

  // Header info: 0x3ff0..0x3fff ("funpaint (mt) ")
  append_header_info(data, std::nullopt);

  // Screen RAMs 1: 0x4000..0x5fe7
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x4000), gunpaint.begin() + gunpaint_data_offset(0x5fe8), data.begin() + funpaint_data_offset(0x4000));

  // Bitmap 1: 0x6000..0x7f3f
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x6000), gunpaint.begin() + gunpaint_data_offset(0x7f40), data.begin() + funpaint_data_offset(0x6000));

  // 100x $d021 colour: 0x7f48..0x7fab
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x7f4f), gunpaint.begin() + gunpaint_data_offset(0x7fb3), data.begin() + funpaint_data_offset(0x7f48));

  // Colour RAM: 0x8000..0x83e7
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x8000), gunpaint.begin() + gunpaint_data_offset(0x83e8), data.begin() + funpaint_data_offset(0x8000));

  // Screen RAMs 2: 0x83e8..0xa3e7
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x8400), gunpaint.begin() + gunpaint_data_offset(0xa3e8), data.begin() + funpaint_data_offset(0x83e8));

  // Bitmap 2: 0xa3e8..0xc327
  std::copy(gunpaint.begin() + gunpaint_data_offset(0xa400), gunpaint.begin() + gunpaint_data_offset(0xc340), data.begin() + funpaint_data_offset(0xa3e8));

  // 100x $d021 colour: 0xc328..0xc38b
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x7fb3), gunpaint.begin() + gunpaint_data_offset(0x8000), data.begin() + funpaint_data_offset(0xc328));
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x87e8), gunpaint.begin() + gunpaint_data_offset(0x87fc), data.begin() + funpaint_data_offset(0xc375));
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x87fb), gunpaint.begin() + gunpaint_data_offset(0x87fc), data.begin() + funpaint_data_offset(0xc389));
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x87fb), gunpaint.begin() + gunpaint_data_offset(0x87fc), data.begin() + funpaint_data_offset(0xc38a));
  std::copy(gunpaint.begin() + gunpaint_data_offset(0x87fb), gunpaint.begin() + gunpaint_data_offset(0x87fc), data.begin() + funpaint_data_offset(0xc38b));

  return data;
}
