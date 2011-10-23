#ifndef CUERPO_H_INCLDED
#define CUERPO_H_INCLDED

#include "Shader.h"

class Cuerpo{
  Shader vertexShader;
  //Shader fragmentShader;
  
  protected:
  GLuint texture;
  float ancho, alto;
  float r,g,b;
  virtual void do_dibujar()=0;
  void cargarTextura(const char * filename);
public:
  Cuerpo();
  void dibujar();
  void setColor(float r, float g, float b);
  float getAlto();
  float getAncho();
  void setVertexShader(Shader s);
};

#endif
