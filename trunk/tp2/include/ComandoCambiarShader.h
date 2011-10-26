#ifndef COMANDOCAMBIARSHADER_H_INCLUDED
#define COMANDOCAMBIARSHADER_H_INCLUDED

#include "Command.h"
#include "Shader.h"

class ComandoCambiarVShaderForma:public Command{
  VertexShader vshader;
public:
  ComandoCambiarVShaderForma(VertexShader vshader);
  virtual void ejecutar();
};

class ComandoCambiarVShaderIluminacion:public Command{
  VertexShader vshader;
public:
  ComandoCambiarVShaderIluminacion(VertexShader vshader);
  virtual void ejecutar();
};

class ComandoCambiarFShader:public Command{
  FragmentShader fshader;
public:
  ComandoCambiarFShader(FragmentShader vshader);
  virtual void ejecutar();
};

#endif
