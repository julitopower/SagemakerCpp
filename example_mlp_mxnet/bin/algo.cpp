#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "sagemaker/sagemaker.hpp"
#include <httplib.h>

#include "mlp.hpp"

namespace {
  struct Hyperparameters {
    std::uint32_t feature_dim;
    std::uint32_t batch_size = 200;
    double learning_rate = 0.01;
    double weight_decay = 0.01;
    std::vector<std::size_t> hidden_layers;
    std::string data_filename;
    std::string labels_filename;
  };

  Hyperparameters get_hyperparameters() {
    sm::Config config{};
    sm::ConfigHelper configHelper{config.hp_file_path};

    Hyperparameters hp;
    hp.feature_dim = configHelper.get_int("feature_dim", 0);
    hp.batch_size = configHelper.get_int("batch_size", hp.batch_size);
    hp.learning_rate = configHelper.get_double("learning_rate", hp.feature_dim);
    hp.weight_decay = configHelper.get_double("weight_decay", hp.weight_decay);

    std::string hidden_layers_str = configHelper.get_string("hidden_layers", "");
    hp.data_filename = configHelper.get_string("data_filename", "");
    hp.labels_filename = configHelper.get_string("labels_filename", "");

    // check compulsory parameters
    if (hp.feature_dim == 0 || hidden_layers_str == "" ||
	hp.data_filename == "" || hp.labels_filename == "") {
      throw std::invalid_argument("Missing required hyperparameters");
    }

    // Hidden layers is basically a set of numbers separated by commas
    std::size_t pos = 0;
    std::string token;
    while ((pos = hidden_layers_str.find(",")) != std::string::npos) {
      token = hidden_layers_str.substr(0, pos);
      hp.hidden_layers.push_back(std::stoi(token));
      hidden_layers_str.erase(0, pos + 1);
      token = hidden_layers_str;
    }
    hp.hidden_layers.push_back(std::stoi(token));
    return hp;
  }
}

void serve() {
  using namespace httplib;
  // https://docs.aws.amazon.com/sagemaker/latest/dg/your-algorithms-inference-code.html
  // Create server object
  Server srv;

  // Install signal handler for SIGTERM. Pass server
  // to handler, so that it can stop it when the time
  // comes
  
  // Register handlers
  srv.get("/ping", [](const Request& req, Response& res) {
      res.status = 200;
      res.body = "OK";
    });

  srv.post("/invocations", [](const Request& req, Response& res) {
      std::cout << "Invocations called" << std::endl;
      Mlp algo{sm::Config{}.model_path};

      //  Here we need to get the body of the request and
      //  dump or wrap it in a file like object.
      std::cout << req.body << std::endl;
      // And finally we call predict

      // If everything went well we return results here
      res.status = 200;
      res.body = "this hould be CSV";
    });  


  // Start loop
  srv.listen("localhost", 8080);
}

int main(int argc, char** argv)
{
  // Initialize signal handlers
  sm::install_signal_handlers();

  // Sagemaker calls us with one argument, but we
  // will assume default is train
  std::string mode {"train"};
  if (argc == 2) {
    mode = std::string{argv[1]};
  }

  if (mode == "serve") {
    serve();
    return 0;
  }

  // Print relevant information
  sm::Config config{};
  // Print a few of the interesting locations in the input
  sm::print_file(config.hp_file_path);
  sm::print_file(config.input_data_config_file_path);
  sm::print_file(config.resources_file_path);

  // For this initial version we assume that a channel called train
  // has been passed. Thus, there will be files under
  // config.input_data_path/train
  std::vector<std::string> files{};
  std::string train_data_dir {config.input_data_path};
  train_data_dir += "train/";
  sm::read_directory(train_data_dir, files);

  for(const auto& file : files)  {
    std::cout << file << std::endl;
  }

  // Let's read the hyperparameters
  auto sm_hp = sm::get_hyperparameters();
  std::cout << sm_hp << std::endl;

  /*
   * Verify that feature_dim and hidden_layers hyperparameters
   * have been provided.
   */
  // Verification is implicit in the hp builder
  auto hp = get_hyperparameters();

  std::cout << "Hyperparameters loaded" << std::endl;
  for (auto& layer : hp.hidden_layers) {
    std::cout  << "layer " << layer << std::endl;
  }
  /* Create MLPParams */
  MlpParams mlpParams(hp.feature_dim, hp.hidden_layers, hp.batch_size);

  /* Createa Mlp */
  Mlp mlp{mlpParams};

  /* Fit */
  std::string data_dir{config.input_data_path};

  std::vector<std::string> datasets {"train/", "test/"};
  std::vector<std::string> filenames {hp.data_filename, hp.labels_filename};
  for (const auto& dataset : datasets) {
    for (const auto& filename : filenames) {
      std::cout << data_dir << dataset << filename << std::endl;
      sm::print_file(data_dir + dataset + filename);
    }
  }

  std::string train_data {data_dir + "train/" + hp.data_filename};
  std::string train_labels {data_dir + "train/" + hp.labels_filename};
  std::string test_data {data_dir + "test/" + hp.data_filename};
  std::string test_labels {data_dir + "test/" + hp.labels_filename};
  mlp.fit(train_data,  train_labels, test_data, test_labels);

  /* Save model to model directory */
  mlp.save_model(config.model_path);
  
  sm::report_success();
  std::cout << "Finished" << std::endl;
  return 0;
}
