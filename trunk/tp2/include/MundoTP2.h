#ifndef MUNDOTP2_H_INCLUDED
#define MUNDOTP2_H_INCLUDED

#include "Mundo.h"
#include "Cuerpo.h"

class MundoTP2: public Mundo{
private:
  Cuerpo *figura;
  float rotX, rotY, rotZ;
  static MundoTP2 *te_odio2;
        
  MundoTP2();
  void display();
  void inicializar();

public:
  static MundoTP2* get_instance();
  void rotarFigura(float angulo, bool x, bool y, bool z);
  void resetearRotacion();
  ~MundoTP2();
};

#endif
