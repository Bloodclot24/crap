#include "ComandoCambiarForma.h"
#include <MundoTP2.h>
#include <Cubo.h>
#include <Esfera.h>

void ComandoCambiarFormaCubo::ejecutar(){
  MundoTP2::get_instance()->cambiarFigura(new Cubo());
}
void ComandoCambiarFormaEsfera::ejecutar(){
MundoTP2::get_instance()->cambiarFigura(new Esfera());
}
