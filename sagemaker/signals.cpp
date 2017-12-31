#include <csignal>
#include <exception>
#include <execinfo.h>
#include <iostream>
#include <unistd.h>

#include <sagemaker/integration.hpp>
#include <sagemaker/signals.hpp>

namespace sm {

  void set_terminate() {
    std::set_terminate([]() {
	std::cout << "Teminating application" << std::endl;
	auto ex = std::current_exception();
	try {
	  std::rethrow_exception(ex);
	} catch(const std::exception& ex) {
	  std::cout << ex.what() << std::endl;
	  // We need to set the failure reason for Sagemaker to
	  // report to customers
	  ::sm::report_failure(std::string{"AlgorithmError: "} + ex.what());
	}
	std::exit(1);      
      });
  }
  
  void set_signal_handlers() {
    void (*handler)(int) = [](int signal) {
      constexpr int MAX_FRAMES = 100;
      void *array[MAX_FRAMES];
      const std::size_t size = backtrace(array, MAX_FRAMES);

      // print out all the frames to stderr
      fprintf(stderr, "Error: signal %d:\n", signal);
      backtrace_symbols_fd(array, size, STDERR_FILENO);
      exit(1);
    };

    std::signal(SIGSEGV, handler);    
  }

  void install_signal_handlers() {
    set_terminate();
    set_signal_handlers();
  }  
}
