#include <iostream>

#include "fileutils.h"
#include "gun2fun.h"
#include "rle.h"

int main(int argc, char **argv) {
  auto [in, out, packed] = parse_args(argc, argv);
  std::cout << "Converting " << in << " to " << out << "...";
  auto gunpaint = read_file(in);
  auto funpaint = convert_data(gunpaint);
  auto data = packed ? pack_data(funpaint) : funpaint;
  write_file(out, data);
  std::cout << " success!" << std::endl;
  return 0;
}
