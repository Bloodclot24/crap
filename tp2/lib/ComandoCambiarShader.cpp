#include "ComandoCambiarShader.h"
#include "MundoTP2.h"

ComandoCambiarShader::ComandoCambiarShader(Shader shader): Command(){
  this->shader = shader;
}

void ComandoCambiarShader::ejecutar(){
      MundoTP2::get_instance()->obtenerCuerpo()->setVertexShader(shader);
}
