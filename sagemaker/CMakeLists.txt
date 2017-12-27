set(SRC file_utils.cpp integration.cpp config_helper.cpp)

add_library(sagemaker ${SRC})

install(TARGETS sagemaker
        LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
