#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>

#include "sagemaker/file_utils.hpp"

namespace sm {
  void print_file(const std::string& path) 
  {
    std::ifstream ifs {path};
    if (!ifs.good()) {
      std::cout << path << " " << " not found." << std::endl;
      return;
    }
    std::cout << "Contents of " << path << std::endl;
    std::cout << ifs.rdbuf() << std::endl;
  }

  void read_directory(const std::string& name, std::vector<std::string>& v)
  {
    DIR* dirp = opendir(name.c_str());

    // Don't do anything if dir doesn't exist
    if (dirp == nullptr) {
      std::cout << name << " " << " not found." << std::endl;      
      return;
    }

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
      v.push_back(dp->d_name);
    }
    closedir(dirp);
  }
}
