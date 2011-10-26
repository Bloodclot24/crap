#include "ComandoCambiarShader.h"
#include "MundoTP2.h"

ComandoCambiarFShader::ComandoCambiarFShader(FragmentShader fshader){
  this->fshader = fshader;
}

void ComandoCambiarFShader::ejecutar(){
  Cuerpo *c = MundoTP2::get_instance()->obtenerCuerpo();
  c->setFshader(fshader);
}

ComandoCambiarVShaderForma::ComandoCambiarVShaderForma(VertexShader vshader){
  this->vshader = vshader;
}

void ComandoCambiarVShaderForma::ejecutar(){
  Cuerpo *c = MundoTP2::get_instance()->obtenerCuerpo();
  c->setVshaderForma(vshader);
}


ComandoCambiarVShaderIluminacion::ComandoCambiarVShaderIluminacion(VertexShader vshader){
  this->vshader = vshader;
}

void ComandoCambiarVShaderIluminacion::ejecutar(){
  Cuerpo *c = MundoTP2::get_instance()->obtenerCuerpo();
  c->setVshaderIluminacion(vshader);
}
