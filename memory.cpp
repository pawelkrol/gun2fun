#include "memory.h"

#include <cstdint>

namespace {

template <uint16_t load_address>
uint16_t data_offset(uint16_t memory_address) {
  return memory_address - load_address + 0x0002;
}

}  // anonymous namesapce

uint16_t funpaint_data_offset(uint16_t memory_address) {
  static constexpr uint16_t load_address = 0x3ff0;
  return data_offset<load_address>(memory_address);
}

uint16_t gunpaint_data_offset(uint16_t memory_address) {
  static constexpr uint16_t load_address = 0x4000;
  return data_offset<load_address>(memory_address);
}
