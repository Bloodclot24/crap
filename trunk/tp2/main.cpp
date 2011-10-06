#include "Mundo.h"
#include "ManejadorTecla.h"

class TeclaVisibilidadPanel : public ManejadorTecla {
  bool press(){
    mundo->cambiarVisibilidadPanel();
    return true;
  }
};

int main(int argc, char** argv)
{
  Mundo m(argc, argv);
  m.crearVentana();
  TeclaVisibilidadPanel mj;
  m.agregarTecla('e', &mj);
  m.comenzar();
  return 0;
}
