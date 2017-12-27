#ifndef CONFIG_HELPER_H
#define CONFIG_HELPER_H

#include <string>
#include <rapidjson/document.h>

namespace sm {
  class ConfigHelper {
  public:
    ConfigHelper(const std::string& file);
    std::string get_string(const std::string& key, 
			   const std::string& default_value) const;
    int get_int(const std::string& key, int default_value) const;
    double get_double(const std::string& key, double default_value) const;
  private:
    rapidjson::Document doc_;
    bool initialized_;
  };
}

#endif /* CONFIG_HELPER_H */
