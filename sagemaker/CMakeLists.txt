set(SRC file_utils.cpp integration.cpp config_helper.cpp)

add_library(sagemaker ${SRC})
set_target_properties(sagemaker 
  PROPERTIES PUBLIC_HEADER "include/integration.hpp;include/Config.hpp;include/file_utils.hpp;include/hyperparameters.hpp")

install(TARGETS sagemaker
        LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include/sagemaker
)
