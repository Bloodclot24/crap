#ifndef COMANDOCAMBIARSHADER_H_INCLUDED
#define COMANDOCAMBIARSHADER_H_INCLUDED

#include "Command.h"
#include "Shader.h"

class ComandoCambiarShader:public Command{
  VertexShader vshader;
  FragmentShader fshader;
public:
  ComandoCambiarShader(VertexShader vshader, FragmentShader fshader);
  virtual void ejecutar();  
};

#endif
