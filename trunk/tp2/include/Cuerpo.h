#ifndef CUERPO_H_INCLDED
#define CUERPO_H_INCLDED

#include "Shader.h"
#include "list"
#include "Animable.h"
#include "Programa.h"

#define INCREMENTO_ANIMACION 0.05

class Cuerpo:public Animable{
  protected:
  GLuint texture;
  GLuint texturaCubica;
  float ancho, alto;
  float r,g,b;
  float pasoAnimacion;
  
  VertexShader vsforma; VertexShader vsFormaSiguiente;
  VertexShader vsiluminacion; VertexShader vsiluminacionSiguiente;
  FragmentShader fs; FragmentShader fsSiguiente;
  bool cambiarShaders;
  
  virtual void do_dibujar()=0;
  virtual void post_dibujar();
  Programa* getProgram();
  
public:
  Cuerpo();
  void dibujar();
  void setColor(float r, float g, float b);
  void setTextura(GLuint t);
  void setTexturaCubica(GLuint t);
  float getAlto();
  float getAncho();
  
  void setVshaderForma(VertexShader vs);
  void setVshaderIluminacion(VertexShader vs);
  void setFshader(FragmentShader fs);
  
  void animar();
};


#endif
