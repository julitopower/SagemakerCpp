set(SRC
  file_utils.cpp
  integration.cpp
  config_helper.cpp
  signals.cpp
  )

add_library(sagemaker ${SRC})

install(TARGETS sagemaker
        LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
