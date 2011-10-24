#ifndef CUERPO_H_INCLDED
#define CUERPO_H_INCLDED

#include "Shader.h"
#include "list"
#include "Animable.h"
#include "Programa.h"

#define INCREMENTO_ANIMACION 0.1

class Cuerpo:public Animable{
  protected:
  GLuint texture;
  float ancho, alto;
  float r,g,b;
  float pasoAnimacion;
  std::list<VertexShader> vss;
  std::list<FragmentShader> fss;
  std::list<VertexShader> vssSiguiente;
  std::list<FragmentShader> fssSiguiente;
  virtual void do_dibujar()=0;
  virtual void post_dibujar();
  Programa* getProgram();
public:
  Cuerpo();
  void dibujar();
  void setColor(float r, float g, float b);
  void setTextura(GLuint t);
  float getAlto();
  float getAncho();
  void agregarShader(VertexShader vs);
  void agregarShader(FragmentShader fs);
  void borrarShaders();
  void animar();
};

#endif
