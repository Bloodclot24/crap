#ifndef CUERPO_H_INCLDED
#define CUERPO_H_INCLDED

#include "Shader.h"
#include "list"

class Cuerpo{
  protected:
  GLuint texture;
  float ancho, alto;
  float r,g,b;
  std::list<VertexShader> vss;
  std::list<FragmentShader> fss;
  virtual void do_dibujar()=0;
  virtual void post_dibujar();
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
};

#endif
