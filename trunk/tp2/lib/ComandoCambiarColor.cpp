#include "ComandoCambiarColor.h"
#include "MundoTP2.h"

ComandoCambiarColor::ComandoCambiarColor(float r, float g, float b){
 this->r=r;
 this->g=g;
 this->b=b;
}

void ComandoCambiarColor::ejecutar(){
  MundoTP2::get_instance()->obtenerCuerpo()->setTextura(NULL);
  MundoTP2::get_instance()->obtenerCuerpo()->setColor(r,g,b);
}
