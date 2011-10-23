#ifndef COMANDOCAMBIARTEXTURA_H_INCLUDED
#define COMANDOCAMBIARTEXTURA_H_INCLUDED

#include "Command.h"
#include <GL/glew.h>
#include <GL/gl.h>

class ComandoCambiarTextura:public Command{
private:
  float r,g,b;
  GLuint texture;
  void cargarTextura(const char * filename);
public:
  ComandoCambiarTextura(const char * filename);
  virtual void ejecutar();
  GLuint getTextura();
};

#endif
