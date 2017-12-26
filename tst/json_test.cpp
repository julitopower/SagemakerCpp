#include <iostream>

#include <rapidjson/document.h>

#include "asserts.hpp"

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
