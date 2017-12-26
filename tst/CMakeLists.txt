set(SRC 
  json_test.cpp
  json_schema.cpp
)

foreach(TEST ${SRC})
  add_executable(${TEST} ${TEST})
  add_test(${TEST}_test ${TEST})
endforeach(TEST)
