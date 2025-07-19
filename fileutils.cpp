#include "fileutils.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

void fail(std::string msg) {
  std::cout << " failed!" << std::endl;
  std::cerr << "Error: " << msg << std::endl;
  exit(1);
}

std::tuple<fs::path, fs::path> parse_args(int argc, char **argv) {
  po::options_description desc
    ("\ngun2fun 1.0.1 - Gunpaint to Funpaint 2 IFLI file converter"
     "\nCopyright (C) 2025-07-19 by Pawel Krol\n"
     "\nUsage: <gun2fun> <input-file.gun> <output-file.fun>"
     "\nArguments");

  desc.add_options()
    ("help", "produce help message")
    ("gunpaint-input-file", po::value<std::string>()->required(), "input file (Gunpaint IFLI picture)")
    ("funpaint-output-file", po::value<std::string>()->required(), "output file (Funpaint 2 IFLI picture)");

  po::positional_options_description pos_desc;
  pos_desc.add("gunpaint-input-file", 1);
  pos_desc.add("funpaint-output-file", 1);

  po::variables_map vm;

  try {
    po::store(po::command_line_parser(argc, argv).
              options(desc).
              positional(pos_desc).
              run(), vm);
    po::notify(vm);
  } catch (po::error& err) {
    std::cerr << "Error: " << err.what() << std::endl;
    std::cerr << desc << std::endl;
    exit(1);
  }

  if (vm.count("help")) {
    std::cerr << desc << std::endl;
    exit(1);
  }


  fs::path in(vm["gunpaint-input-file"].as<std::string>());
  fs::path out(vm["funpaint-output-file"].as<std::string>());

  if (!fs::exists(in) || !fs::is_regular_file(in)) {
    std::cerr << "Error: file '" << in << "' does not exist" << std::endl;
    std::cerr << desc << std::endl;
    exit(1);
  }

  if (fs::exists(out)) {
    std::cerr << "Error: file '" << out << "' already exists" << std::endl;
    std::cerr << desc << std::endl;
    exit(1);
  }

  return std::make_tuple(in, out);
}

std::vector<char> read_file(fs::path file) {
  std::string path = fs::canonical(file).string();
  std::ifstream ifs(path, std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    fail(std::string("Unable to open file: ") + path);
  }
  const std::size_t& size = fs::file_size(path);
  std::vector<char> content(size);
  ifs.read(content.data(), size);
  ifs.close();
  return content;
}

void write_file(fs::path file, const std::vector<char>& content) {
  std::string path = fs::absolute(file).string();
  std::ofstream ofs(path, std::ios::out | std::ios::binary);
  if (!ofs.is_open()) {
    fail(std::string("Unable to open file: ") + path);
  }
  ofs.write(content.data(), content.size());
  ofs.close();
}
