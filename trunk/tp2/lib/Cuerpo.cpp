#include "Cuerpo.h"
#include <GL/gl.h>
#include <vector>
#include <Programa.h>

void Cuerpo::dibujar(){
 glColor3f(r,g,b);
 Programa::crearPrograma(vss, fss)->usar();
 
 do_dibujar();
 post_dibujar();
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
    texture = NULL;
}

void Cuerpo::setColor(float r, float g, float b){
  this->r=r;
  this->g=g;
  this->b=b;
  
}

void Cuerpo::agregarShader(VertexShader vs){
  vss.push_back(vs);
}

void Cuerpo::agregarShader(FragmentShader fs){
  fss.push_back(fs);
}

void Cuerpo::borrarShaders(){
  vss.clear();
  fss.clear();
}

void Cuerpo::setTextura(GLuint t){
	texture = t;
}

void Cuerpo::post_dibujar(){
  glUseProgram(0);
}
