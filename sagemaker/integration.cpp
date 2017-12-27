#include <fstream>
#include <string>

#include "sagemaker/Config.hpp"
#include "sagemaker/config_helper.hpp"
#include "sagemaker/integration.hpp"


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

  Hyperparameters get_hyperparameters() {
    sm::Config config{};
    sm::ConfigHelper configHelper{config.hp_file_path};

    Hyperparameters hp;
    hp.feature_dim = configHelper.get_int("feature_dim", 0);
    hp.learning_rate = configHelper.get_double("learning_rate", 0.01d);
    return hp;
  }  
}
