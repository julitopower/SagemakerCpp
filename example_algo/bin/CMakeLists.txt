set(SRC algo.cpp)

add_executable(algo ${SRC})
target_link_libraries(algo sagemaker)

install(TARGETS algo
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
