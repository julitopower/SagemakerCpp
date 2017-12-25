#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <string>

namespace sm {
  void report_success();
  void resport_failure(const std::string& message);
  void write_model(const std::string& name, std::istream& content);
}

#endif /* INTEGRATION_H */
