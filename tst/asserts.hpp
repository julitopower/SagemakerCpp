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
