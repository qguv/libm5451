// ensure this library description is only included once
#ifndef Sixteen_h
#define Sixteen_h

// include types & constants of Wiring core API
#include "WConstants.h"

// library interface description
class Sixteen {

  // user-accessible "public" interface
  public:
    Sixteen(int);
    void doSomething(void);

  // library-accessible "private" interface
  private:
    int value;
    void doSomethingSecret(void);
};

#endif
