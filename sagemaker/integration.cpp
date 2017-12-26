#include <fstream>
#include <string>

#include "Config.hpp"
#include "integration.hpp"


namespace sm {
  void report_success() {
    sm::Config config{};
    std::ofstream completed {std::string{config.output_path} + "completed"};
    completed << "OK";
  }

  void resport_failure(const std::string& message) {
    sm::Config config{};
    std::ofstream failure{std::string{config.failure_file_path}};
    failure << message;
  }

  void write_model(const std::string& name, std::istream& content) {
    sm::Config config{};
    std::ofstream model{std::string{config.model_path} + name};
    model << content.rdbuf();
  }
  
}
