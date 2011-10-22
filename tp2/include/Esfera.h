#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "Cuerpo.h"

class Esfera: public Cuerpo{
private:
	void construirEsfera(double R);
	void mostrarEsfera(double R/*, GLuint texture*/);
protected:
  virtual void do_dibujar();
public:
  Esfera();
  
};

#endif
