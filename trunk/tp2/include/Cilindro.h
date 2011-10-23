#ifndef CILINDRO_H_
#define CILINDRO_H_


#include "Cuerpo.h"

class Cilindro: public Cuerpo{
private:
	void dibujarCirculo(int segmentos);
protected:
  virtual void do_dibujar();
public:
  Cilindro();
};

#endif /* CILINDRO_H_ */
