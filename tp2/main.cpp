#include "Shader.h"
#include "MundoTP2.h"
#include "ManejadorTecla.h"
#include "Cubo.h"
#include <stdlib.h>

#define ANGULO_ROTACION 2

class TeclaRotarX: public ManejadorTecla{
public:
    virtual bool press(){
     MundoTP2::get_instance()->rotarFigura(ANGULO_ROTACION, 1, 0, 0);
     return true;
    }
};

class TeclaRotarY: public ManejadorTecla{
public:
    virtual bool press(){
     MundoTP2::get_instance()->rotarFigura(ANGULO_ROTACION, 0, 1, 0);
     return true;
    }
};

class TeclaRotarZ: public ManejadorTecla{
public:
    virtual bool press(){
     MundoTP2::get_instance()->rotarFigura(ANGULO_ROTACION, 0, 0, 1);
     return true;
    }
};

class TeclaResetearRotacion: public ManejadorTecla{
public:
    virtual bool press(){
     MundoTP2::get_instance()->resetearRotacion();
     return true;
    }
};

class TeclaSalir: public ManejadorTecla{
public:
    virtual bool press(){
     exit(0);
     return true;
    }
};



int main(int argc, char** argv)
{
  MundoTP2 *m = MundoTP2::get_instance();
  TeclaRotarX rotarx; TeclaRotarY rotary; TeclaRotarZ rotarz;
  TeclaResetearRotacion resetr;
  TeclaSalir salir;
  m->crearVentana();
  m->agregarTecla('x', &rotarx);
  m->agregarTecla('y', &rotary);
  m->agregarTecla('z', &rotarz);
  m->agregarTecla('r', &resetr);
  m->agregarTecla('q', &salir);
  atexit(MundoTP2::destruir);
  m->comenzar();
  return 0;
}
