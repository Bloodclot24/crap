#include "Cuerpo.h"
#include <GL/gl.h>
#include <vector>
#include <Programa.h>
#include <MundoTP2.h>

void Cuerpo::dibujar(){
 glColor3f(r,g,b);
 glBindTexture (GL_TEXTURE_2D, texture);
 
 Programa* p = getProgram();
 if(p){
   p->usar();
   p->cambiarUniforme("usar_textura",texture);
   p->cambiarUniforme("t", pasoAnimacion);
 }
 
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
    pasoAnimacion=0;
    MundoTP2::get_instance()->animame(this,10);
}

void Cuerpo::setColor(float r, float g, float b){
  this->r=r;
  this->g=g;
  this->b=b;
}

void Cuerpo::agregarShader(VertexShader vs){
    vssSiguiente.push_back(vs);
}

void Cuerpo::agregarShader(FragmentShader fs){
    fssSiguiente.push_back(fs);
}

Programa* Cuerpo::getProgram(){
  return Programa::crearPrograma(vss, fss);
}

void Cuerpo::borrarShaders(){
  vssSiguiente.clear();
  fssSiguiente.clear();
}

void Cuerpo::setTextura(GLuint t){
  texture = t;
}

void Cuerpo::setTexturaCubica(GLuint t){
  texturaCubica = t;
}

void Cuerpo::post_dibujar(){
  glUseProgram(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Cuerpo::animar(){
  if(vssSiguiente.size() > 0){ //animacion para abajo
      if(pasoAnimacion > 0)
	pasoAnimacion -= INCREMENTO_ANIMACION;
      else{
	vss = vssSiguiente;
	vssSiguiente.clear();
	fss = fssSiguiente;
	fssSiguiente.clear();
      }
  }
  else{
    if(pasoAnimacion<1)
      pasoAnimacion += INCREMENTO_ANIMACION; 
  }
  
  MundoTP2::get_instance()->animame(this,50);
}

