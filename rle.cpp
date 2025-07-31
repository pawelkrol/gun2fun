#include "rle.h"

#include "funpaint.h"
#include "memory.h"

#include <algorithm>
#include <array>
#include <boost/preprocessor/repetition/enum.hpp>
#include <cstdint>
#include <tuple>
#include <vector>

namespace {

#define HIST_ELEMENT(z, n, data) {n, data}

struct {
  bool operator()(const std::tuple<char, uint16_t>& a, const std::tuple<char, uint16_t>& b) const {
    if (std::get<1>(a) < std::get<1>(b))
      return true;
    else
      if (std::get<1>(a) > std::get<1>(b))
        return false;
      else
        return static_cast<uint8_t>(std::get<0>(a)) < static_cast<uint8_t>(std::get<0>(b));
  }
} customLess;

char8_t rle_escape(const std::vector<char>& data) {
  auto head = data.cbegin() + 0x000e;

  std::array<std::tuple<char, uint16_t>, 256> hist{
    { BOOST_PP_ENUM(256, HIST_ELEMENT, 0) }
  };

  std::for_each(head, data.cend(), [&hist](const char& c) {
    ++std::get<1>(hist.at(c & 0xff));
  });

  std::sort(hist.begin(), hist.end(), customLess);

  return std::get<0>(hist.front());
}

void append_data_bytes(uint8_t& c_count, char cur_c, std::vector<char>& data, char8_t escape) {
  if (c_count > 2 || static_cast<char8_t>(cur_c) == escape) {
    data.push_back(escape);
    data.push_back(c_count);
    data.push_back(cur_c);
  }
  else {
    while (c_count--) {
      data.push_back(cur_c);
    }
  }
  c_count = 0;
}

}  // anonymous namesapce

std::vector<char> pack_data(std::vector<char>& funpaint) {
  std::vector<char> data{};
  data.reserve(funpaint.size());
  data.resize(0x0012);

  std::vector<uint16_t> offsets{
    0x43f8, 0x47f8, 0x4bf8, 0x4ff8, 0x53f8, 0x57f8, 0x5bf8, 0x5ff8,
    0x87e0, 0x8be0, 0x8fe0, 0x93e0, 0x97e0, 0x9be0, 0x9fe0, 0xa3e0,
  };
  std::for_each(offsets.cbegin(), offsets.cend(), [&funpaint](uint16_t offset) {
    funpaint.at(funpaint_data_offset(offset)) = 0xff;
  });

  // Load address: 0x3ff0
  append_load_address(data);

  auto escape = rle_escape(funpaint);

  // Header info: 0x3ff0..0x3fff ("funpaint (mt) ")
  append_header_info(data, escape);

  auto head = funpaint.cbegin() + 0x0012;

  uint8_t c_count = 1;
  char cur_c = *(head++);
  std::for_each(head, funpaint.cend(), [&](const char& c) {
    if (cur_c != c || c_count == 0xff) {
      append_data_bytes(c_count, cur_c, data, escape);
      cur_c = c;
    }
    ++c_count;
  });
  append_data_bytes(c_count, cur_c, data, escape);

  append_data_bytes(++c_count, 0xa3, data, 0xff);
  append_data_bytes(++c_count, 0x00, data, 0xff);

  return data;
}
