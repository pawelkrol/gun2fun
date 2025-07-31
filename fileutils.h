#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <tuple>
#include <vector>

void fail(std::string);

std::tuple<boost::filesystem::path, boost::filesystem::path, bool> parse_args(int, char **);

std::vector<char> read_file(boost::filesystem::path);

void write_file(boost::filesystem::path, const std::vector<char>&);
