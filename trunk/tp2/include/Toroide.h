#ifndef TOROIDE_H_INCLUDED
#define TOROIDE_H_INCLUDED

#include "Cuerpo.h"

class Toroide: public Cuerpo{
protected:
  virtual void do_dibujar();
public:
  Toroide();
};

#endif
