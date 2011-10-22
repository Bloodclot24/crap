#ifndef COMANDOCAMBIARSHADER_H_INCLUDED
#define COMANDOCAMBIARSHADER_H_INCLUDED

#include "Command.h"
#include "Shader.h"

class ComandoCambiarShader:public Command{
  Shader shader;
public:
  ComandoCambiarShader(Shader shader);
  virtual void ejecutar();  
};

#endif
