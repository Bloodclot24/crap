#ifndef COMANDOCAMBIARTEXTURACUBICA_H_INCLUDED
#define COMANDOCAMBIARTEXTURACUBICA_H_INCLUDED

#include "Command.h"
#include <GL/glew.h>
#include <GL/gl.h>

class ComandoCambiarTexturaCubica:public Command{
private:
  GLuint texture;
  void cargarTextura(const char * filename);
public:
  ComandoCambiarTexturaCubica(const char * filename);
  virtual void ejecutar();
  GLuint getTextura();
};

#endif
