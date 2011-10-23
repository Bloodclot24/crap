#ifndef CONO_H_
#define CONO_H_

#include "Cuerpo.h"

class Cono: public Cuerpo{
private:
	void dibujarCirculo(int segmentos);
protected:
  virtual void do_dibujar();
public:
  Cono();
};

#endif /* CONO_H_ */
