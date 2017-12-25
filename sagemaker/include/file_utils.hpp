#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

namespace sm {
  void print_file(const std::string& path);
  void read_directory(const std::string& name, std::vector<std::string>& v);
}

#endif /* FILE_UTILS_H */
