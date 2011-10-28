#include "Shader.h"
#include "MundoTP2.h"
#include "ManejadorTecla.h"
#include "Cubo.h"
#include <stdlib.h>

#define ANGULO_ROTACION 2

class TeclaRotarX: public ManejadorTecla{
private:
  int signo;
public:
    TeclaRotarX(int s) {
      signo = s;
    }
    virtual bool press(){
     MundoTP2::get_instance()->rotarFigura(signo*ANGULO_ROTACION, 1, 0, 0);
     return true;
    }
};

class TeclaRotarY: public ManejadorTecla{
private:
  int signo;
public:
    TeclaRotarY(int s) {
      signo = s;
    }
    virtual bool press(){
     MundoTP2::get_instance()->rotarFigura(signo*ANGULO_ROTACION, 0, 1, 0);
     return true;
    }
};

class TeclaRotarZ: public ManejadorTecla{
private:
  int signo;
public:
    TeclaRotarZ(int s) {
      signo = s;
    }
    virtual bool press(){
     MundoTP2::get_instance()->rotarFigura(signo*ANGULO_ROTACION, 0, 0, 1);
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

class TeclaCapturarMouse: public ManejadorTecla{
public:
    virtual bool press(){
     MundoTP2::get_instance()->capturar_mouse();
     return true;
    }
};

class TeclaLuz1: public ManejadorTecla{
public:
    virtual bool press(){
     MundoTP2::get_instance()->cambiar_estado_luz_1();
     return true;
    }
};

class TeclaLuz2: public ManejadorTecla{
public:
    virtual bool press(){
     MundoTP2::get_instance()->cambiar_estado_luz_2();
     return true;
    }
};

class TeclaMenu: public ManejadorTecla{
public:
    virtual bool press(){
     MundoTP2::get_instance()->cambiar_estado_menu();
     return true;
    }
};

int main(int argc, char** argv)
{
  MundoTP2 *m = MundoTP2::get_instance();
  TeclaRotarX rotarx(1); TeclaRotarY rotary(1); TeclaRotarZ rotarz(1);
  TeclaRotarX rotarMenosx(-1); TeclaRotarY rotarMenosy(-1); TeclaRotarZ rotarMenosz(-1);
  TeclaResetearRotacion resetr;
  TeclaSalir salir;
  TeclaCapturarMouse capturar;
  TeclaLuz1 luz1;
  TeclaLuz2 luz2;
  TeclaMenu menu;
  m->crearVentana();
  m->agregarTecla('x', &rotarx);
  m->agregarTecla('s', &rotarMenosx);
  m->agregarTecla('y', &rotary);
  m->agregarTecla('Y', &rotarMenosy);
  m->agregarTecla('z', &rotarz);
  m->agregarTecla('Z', &rotarMenosz);
  m->agregarTecla('r', &resetr);
  m->agregarTecla('q', &salir);
  m->agregarTecla('c', &capturar);
  m->agregarTecla('1', &luz1);
  m->agregarTecla('2', &luz2);
  m->agregarTecla('m', &menu);
  atexit(MundoTP2::destruir);
  m->comenzar();
  return 0;
}

