#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "sagemaker/Config.hpp"
#include "sagemaker/file_utils.hpp"
#include "sagemaker/integration.hpp"

int main(int argc, char** argv)
{
  // Print a few of the interesting locations in the input
  sm::Config config{};
  sm::print_file(config.hp_file_path);
  sm::print_file(config.input_data_config_file_path);
  sm::print_file(config.resources_file_path);

  // For this initial version we assume that a channel called train
  // has been passed. Thus, there will be files under
  // config.input_data_path/train
  std::vector<std::string> files{};
  std::string train_data {config.input_data_path};
  train_data += "train/";
  sm::read_directory(train_data, files);

  for(const auto& file : files)  {
    std::cout << file << std::endl;
  }

  // Let's read the hyperparameters
  auto hp = sm::get_hyperparameters();
  std::cout << hp << std::endl;

  sm::report_success();
  std::stringstream message{};
  message << "This is my model message";
  sm::write_model("model_file.txt", message);
  return 0;
}
