#include "Cuerpo.h"
#include <GL/gl.h>

void Cuerpo::dibujar(){
 //poner shaders
 //estado de animación
 glColor3f(r,g,b);
 do_dibujar();
}

float Cuerpo::getAlto(){
  return alto;
}

float Cuerpo::getAncho(){
  return ancho;
}

Cuerpo::Cuerpo(){
    alto=1;
    ancho=1;
    r=g=b=0.5;
}

void Cuerpo::setColor(float r, float g, float b){
  this->r=r;
  this->g=g;
  this->b=b;
}
