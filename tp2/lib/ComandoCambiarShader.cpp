#include "ComandoCambiarShader.h"
#include "MundoTP2.h"

ComandoCambiarShader::ComandoCambiarShader(VertexShader vshader, FragmentShader fshader): Command(){
  this->vshader = vshader;
  this->fshader = fshader;
}

void ComandoCambiarShader::ejecutar(){
    Cuerpo *c = MundoTP2::get_instance()->obtenerCuerpo();
    c->borrarShaders();
    c->agregarShader(vshader);
    c->agregarShader(fshader);
}

ComandoCambiarFShader::ComandoCambiarFShader(FragmentShader fshader){
  this->fshader = fshader;
}

void ComandoCambiarFShader::ejecutar(){
  Cuerpo *c = MundoTP2::get_instance()->obtenerCuerpo();
  VertexShader vshader = c->obtenerVshader();
  c->borrarShaders();
  c->agregarShader(vshader);
  c->agregarShader(fshader);
}

ComandoCambiarVShader::ComandoCambiarVShader(VertexShader vshader){
  this->vshader = vshader;
}

void ComandoCambiarVShader::ejecutar(){
  Cuerpo *c = MundoTP2::get_instance()->obtenerCuerpo();
  FragmentShader fshader = c->obtenerFshader();
  c->borrarShaders();
  c->agregarShader(vshader);
  c->agregarShader(fshader);
}
