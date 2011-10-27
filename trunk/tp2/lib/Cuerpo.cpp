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
   std::vector<bool> luces = MundoTP2::get_instance()->obtenerEstadoLuces();
   p->cambiarUniforme("light0", luces[0]);
   p->cambiarUniforme("light1", luces[1]);
 }
  glRotatef(ax, 1,0,0);
  glRotatef(ay, 0,1,0);
  glRotatef(az, 0,0,1);
  
  p  = getProgram();
  if(p){
    //glLoadIdentity();
    p->cambiarUniforme("matriz_mv",  MundoTP2::get_instance()->getMatrizCamara());
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
    cambiarShaders=0;
    MundoTP2::get_instance()->animame(this,10);
    ax=ay=az=0;
}

void Cuerpo::setColor(float r, float g, float b){
  this->r=r;
  this->g=g;
  this->b=b;
}


void Cuerpo::setFshader(FragmentShader fs){
  if(!cambiarShaders){
    vsFormaSiguiente = vsforma;
    vsiluminacionSiguiente = vsiluminacion;
  }
  fsSiguiente = fs;
  cambiarShaders = true;
}

void Cuerpo::setVshaderForma(VertexShader vs){
  if(!cambiarShaders){
    fsSiguiente = fs;
    vsiluminacionSiguiente = vsiluminacion;
  }
  vsFormaSiguiente = vs;
  cambiarShaders = true;
}

void Cuerpo::setVshaderIluminacion(VertexShader vs){
  std::cout << "Cambio el shader de iluminacion por " << vs.getId() << "\n";
  if(!cambiarShaders){
    fsSiguiente = fs;
    vsFormaSiguiente = vsforma;
  }
  vsiluminacionSiguiente = vs;
  cambiarShaders = true;
}

Programa* Cuerpo::getProgram(){
  std::list<VertexShader> vss;
  std::list<FragmentShader> fss;
  vss.push_back(vsforma); vss.push_back(vsiluminacion);
  fss.push_back(fs);
  return Programa::crearPrograma(vss, fss);
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
  if(cambiarShaders){ //animacion para abajo
      if(pasoAnimacion > 0)
	pasoAnimacion -= INCREMENTO_ANIMACION;
      else{
	vsforma = vsFormaSiguiente;
	vsiluminacion = vsiluminacionSiguiente;
	fs = fsSiguiente;
	cambiarShaders = false;
      }
  }
  else{
    if(pasoAnimacion<1)
      pasoAnimacion += INCREMENTO_ANIMACION; 
  }
  
  MundoTP2::get_instance()->animame(this,50);
}



void Cuerpo::rotarX(float angulo){
  ax += angulo;
}
void Cuerpo::rotarY(float angulo){
  ay += angulo;
}
void Cuerpo::rotarZ(float angulo){
  az += angulo;
}
void Cuerpo::setRotacion(float ax, float ay, float az){
  this->ax = ax;
  this->ay=ay;
  this->az=az;
}
