#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "Cuerpo.h"

class Cubo: public Cuerpo{
private:
	void cuadradoMedio();
protected:
  virtual void do_dibujar();
  
};

#endif
