#ifndef HYPERPARAMETERS_H
#define HYPERPARAMETERS_H

#include <iostream>

namespace sm {
  struct Hyperparameters {
    std::uint32_t feature_dim = 0;
    double learning_rate = 0.01;
  };

  inline std::ostream& operator<<(std::ostream& os, const Hyperparameters& hp) {
    os << "feature_dim: " << hp.feature_dim << ", learning_rate: " << 
      hp.learning_rate << std::endl;
    return os;
  }
}

#endif /* HYPERPARAMETERS_H */
