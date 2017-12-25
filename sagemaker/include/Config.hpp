#ifndef CONFIG_H
#define CONFIG_H

namespace sm {
  /*
    Checkout AWS Sagemaker schema in :
    http://docs.aws.amazon.com/sagemaker/latest/dg/your-algorithms-training-algo.html
  */
  struct Config {
    const char* const failure_file_path = "/opt/ml/output/failure";
    const char* const hp_file_path = "/opt/ml/input/config/hyperparameters.json";
    const char* const input_data_config_file_path = "/opt/ml/input/config/inputdataconfig.json";
    const char* const input_data_path = "/opt/ml/input/data/";
    const char* const model_path = "/opt/ml/model/";
    const char* const output_path = "/opt/ml/output/";
    const char* const resources_file_path = "/opt/ml/input/config/resourceconfig.json";
  };
}

#endif /* CONFIG_H */
