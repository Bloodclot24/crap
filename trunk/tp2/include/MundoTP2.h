#ifndef MUNDOTP2_H_INCLUDED
#define MUNDOTP2_H_INCLUDED

#include "Mundo.h"

class MundoTP2: public Mundo{
private:
  void display();
public:
  static Mundo* get_instance();
};

#endif
