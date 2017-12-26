#include <iostream>
#include <cassert>
#include <rapidjson/document.h>

#define ASSERT_MSG(expr, msg)				\
  {							\
    if (!expr) {					\
      std::cerr << "Error: " << msg << std::endl;	\
      exit(1);						\
    }							\
  }

#define ASSERT(expr)					\
  {							\
    const char* const msg = "Test failure";		\
    if (!expr) {					\
      std::cerr << "Error: " << msg << std::endl;	\
      exit(1);						\
    }							\
  }

int main(int argc, char** argv)
{
  const char* const json = R"(
     {"key" : "value"}
  )";

  namespace j = rapidjson;
  j::Document doc;
  doc.Parse(json);
  ASSERT_MSG(doc.IsObject(), "Document should be Object");
  ASSERT(doc.HasMember("key"));
  return 0;
}
