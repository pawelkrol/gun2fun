#include <iostream>

#include "fileutils.h"
#include "gun2fun.h"

int main(int argc, char **argv) {
  auto [in, out] = parse_args(argc, argv);
  std::cout << "Converting " << in << " to " << out << "...";
  auto gunpaint = read_file(in);
  auto funpaint = convert_data(gunpaint);
  write_file(out, funpaint);
  std::cout << " success!" << std::endl;
  return 0;
}
