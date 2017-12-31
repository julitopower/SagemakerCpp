#ifndef SIGNALS_H
#define SIGNALS_H

namespace sm {
  /*
    Installs a terminate handler
  */
  void set_terminate();

  /*
    Sets signal handler for SIG_SEV
  */
  void set_signal_handlers();

  /* 
     Sets both terminate and SIGSEGV handlers
  */
  void install_signal_handlers();
}

#endif /* SIGNALS_H */
