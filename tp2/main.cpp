#include "Shader.h"
#include "MundoTP2.h"
#include "ManejadorTecla.h"
#include "Cubo.h"

int main(int argc, char** argv)
{

  Mundo *m = MundoTP2::get_instance();
  m->crearVentana();
  m->comenzar();
  return 0;
}
