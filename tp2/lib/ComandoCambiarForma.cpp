#include "ComandoCambiarForma.h"
#include "MundoTP2.h"
#include "Cubo.h"
#include "Esfera.h"
#include "Toroide.h"
#include "Cilindro.h"
#include "Cono.h"

void ComandoCambiarFormaCubo::ejecutar(){
  MundoTP2::get_instance()->cambiarFigura(new Cubo());
}
void ComandoCambiarFormaEsfera::ejecutar(){
MundoTP2::get_instance()->cambiarFigura(new Esfera());
}
void ComandoCambiarFormaToroide::ejecutar(){
MundoTP2::get_instance()->cambiarFigura(new Toroide());
}
void ComandoCambiarFormaCilindro::ejecutar(){
MundoTP2::get_instance()->cambiarFigura(new Cilindro());
}
void ComandoCambiarFormaCono::ejecutar(){
MundoTP2::get_instance()->cambiarFigura(new Cono());
}
