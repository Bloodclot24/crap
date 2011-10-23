#include "ComandoCambiarShader.h"
#include "MundoTP2.h"

ComandoCambiarShader::ComandoCambiarShader(VertexShader vshader, FragmentShader fshader): Command(){
  this->vshader = vshader;
  this->fshader = fshader;
}

void ComandoCambiarShader::ejecutar(){
      MundoTP2::get_instance()->obtenerCuerpo()->setShader(vshader);
      MundoTP2::get_instance()->obtenerCuerpo()->setShader(fshader);
}
