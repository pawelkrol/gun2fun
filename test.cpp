#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "fileutils.h"
#include "gun2fun.h"
#include "rle.h"

#include "doctest/doctest.h"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace {

const auto fixtures = fs::path("fixtures");

const auto image_fun        = fixtures / "image.fun";
const auto image_gun        = fixtures / "image.gun";
const auto image_packed_fun = fixtures / "image-packed.fun";

}  // anonymous namesapce

TEST_CASE("convert_data") {
  auto gunpaint = read_file(image_gun);
  auto funpaint = convert_data(gunpaint);
  CHECK(funpaint == read_file(image_fun));
}

TEST_CASE("pack_data") {
  auto gunpaint = read_file(image_gun);
  auto funpaint = convert_data(gunpaint);
  auto data = pack_data(funpaint);
  CHECK(data == read_file(image_packed_fun));
}
