#include <fstream>
#include <iostream>
#include <stdexcept>
#include <rapidjson/document.h>
#include <rapidjson/schema.h>
#include <config_helper.hpp>

#define GET_KEY(key, def, type)						\
  auto keyc = key.data();						\
  if (initialized_ && doc_.HasMember(keyc) && doc_[keyc].Is##type()) {	\
    return doc_[keyc].Get##type();					\
  }									\
  return def;

#define GET_VALUE(key, def, type, conv)				\
    auto keyc = key.data();					\
    if (initialized_ && doc_.HasMember(keyc)) {			\
      if (doc_[keyc].Is##type()) {				\
	return doc_[keyc].Get##type();				\
      } else if (doc_[keyc].IsString()) {			\
	try {							\
	  return conv(std::string{doc_[keyc].GetString()});	\
	} catch (const std::invalid_argument& ia) {		\
	  std::cout << ia.what() << std::endl;			\
	  return def;						\
	}							\
      }								\
    }								\
    return def;

namespace sm {

  ConfigHelper::ConfigHelper(const std::string& file) : doc_{}, 
							initialized_(false)
  {
    std::ifstream ifs {file};
    std::string str((std::istreambuf_iterator<char>(ifs)),
		    std::istreambuf_iterator<char>());
    doc_.Parse(str.data());
    initialized_ = !doc_.HasParseError();
  }

  std::string ConfigHelper::get_string(const std::string& key,
				       const std::string& default_value) const 
  {
    GET_KEY(key, default_value, String);
  }

  int ConfigHelper::get_int(const std::string& key, int default_value) const {
    GET_VALUE(key, default_value, Int, stoi);
  }

  double ConfigHelper::get_double(const std::string& key, double default_value) const {
    GET_VALUE(key, default_value, Double, stod);
  }

}
