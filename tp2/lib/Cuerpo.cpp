#include "Cuerpo.h"
#include <GL/gl.h>
#include <vector>

void Cuerpo::dibujar(){
 glColor3f(r,g,b);
 //glUseProgram(vertexShader.getProgram());
 if(vs.getId() != 0){
  GLint program = glCreateProgram();
  glAttachShader(program, vs.getId());
  glAttachShader(program, fs.getId());
  glLinkProgram(program);
  glUseProgram(program);
  std::vector<char> log;
  log.reserve(500);
  int longitud;
  glGetShaderInfoLog(program, 500, &longitud, &log[0]);
  std::string retorno(&log[0]);  
  std::cout << "LOGLINK: " << retorno << "\n";
 }
 
 do_dibujar();
 post_dibujar();
}

float Cuerpo::getAlto(){
  return alto;
}

float Cuerpo::getAncho(){
  return ancho;
}

Cuerpo::Cuerpo(){
    alto=1;
    ancho=1;
    r=g=b=0.5;
    texture = NULL;
}

void Cuerpo::setColor(float r, float g, float b){
  this->r=r;
  this->g=g;
  this->b=b;
  
}

void Cuerpo::setTextura(GLuint t){
	texture = t;
}

void Cuerpo::setShader(VertexShader vs){
  this->vs = vs;
}

void Cuerpo::setShader(FragmentShader fs){
  this->fs =fs;
}

void Cuerpo::post_dibujar(){
  glUseProgram(0);
}
