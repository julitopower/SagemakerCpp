set(HDRS 
  sagemaker/Config.hpp
  sagemaker/config_helper.hpp
  sagemaker/file_utils.hpp
  sagemaker/hyperparameters.hpp
  sagemaker/integration.hpp
)

install(FILES ${HDRS}
  DESTINATION include/sagemaker/
)
