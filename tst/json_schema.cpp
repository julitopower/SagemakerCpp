#include <iostream>

#include <rapidjson/schema.h>

#include "asserts.hpp"

int main(int argc, char** argv)
{
  const char* const schema_json = R"(
  {
    "title": "Person",
    "type": "object",
    "properties": {
        "firstName": {
            "type": "string"
        },
        "lastName": {
            "type": "string"
        },
        "age": {
            "description": "Age in years",
            "type": "integer",
            "minimum": 0
        }
    },
    "required": ["firstName", "lastName"]
  }
  )";

  const char* const valid_json = R"(
  {
    "firstName" : "Julio",
    "lastName" : "Delgado"
  }
  )";

  const char* const invalid_json = R"(
  {
    "firstNames" : "Julio",
    "lastName" : "Delgado"
  }
  )";

  namespace j = rapidjson;

  // Load the schema
  j::Document sd;
  sd.Parse(schema_json);
  j::SchemaDocument schema{sd};

  // Load and validate the valid json
  j::Document good_json;
  good_json.Parse(valid_json);
  j::SchemaValidator validator{schema};
  ASSERT_MSG(good_json.Accept(validator), "Could validate document");

  // Load and validate the invalid json
  j::Document bad_json;
  bad_json.Parse(invalid_json);
  ASSERT_MSG(!bad_json.Accept(validator), "Validation should have failed");

  return 0;
}

