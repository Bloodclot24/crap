#ifndef CUERPO_H_INCLDED
#define CUERPO_H_INCLDED

#include "Shader.h"

class Cuerpo{
  protected:
  GLuint texture;
  float ancho, alto;
  float r,g,b;
  VertexShader vs;
  FragmentShader fs;
  virtual void do_dibujar()=0;
  void cargarTextura(const char * filename);
public:
  Cuerpo();
  void dibujar();
  void setColor(float r, float g, float b);
  float getAlto();
  float getAncho();
  void setShader(VertexShader vs);
  void setShader(FragmentShader fs);
};

#endif
