#include "Cuerpo.h"
#include <GL/gl.h>
#include <vector>
#include <Programa.h>
#include <MundoTP2.h>

void Cuerpo::dibujar(){
 glColor3f(r,g,b);
 
 Programa* p = getProgram();
 if(p)
   p->usar();
 
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
    pasoAnimacion=0.1;
    //MundoTP2::get_instance()->animame(this,5);
}

void Cuerpo::setColor(float r, float g, float b){
  this->r=r;
  this->g=g;
  this->b=b;
}

void Cuerpo::agregarShader(VertexShader vs){
  //if(pasoAnimacion > 0)
  //  vssSiguiente.push_back(vs);
  //else
    vss.push_back(vs);
}

void Cuerpo::agregarShader(FragmentShader fs){
  //if(pasoAnimacion > 0)
  //  fssSiguiente.push_back(fs);
  //else
    fss.push_back(fs);
}

Programa* Cuerpo::getProgram(){
  return Programa::crearPrograma(vss, fss);
}

void Cuerpo::borrarShaders(){
  vssSiguiente.clear();
  fssSiguiente.clear();
  vss.clear();
  fss.clear();
}

void Cuerpo::setTextura(GLuint t){
  texture = t;
}

void Cuerpo::post_dibujar(){
  glUseProgram(0);
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
  
  Programa* p = Programa::crearPrograma(vss, fss);
  if(p)
    p->cambiarUniforme("t", pasoAnimacion);
  std::cout << "t: " << pasoAnimacion << "\n";
  MundoTP2::get_instance()->animame(this,500);
}

