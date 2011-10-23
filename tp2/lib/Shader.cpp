#include "Shader.h"
#include <fstream>
#include <vector>

Shader::Shader(){
    shader = 0;
}

bool Shader::cargarDesdeArchivo(std::string nombre, GLenum tipo){
  shader = glCreateShader(tipo);
  std::string codigo;
  char buffer[200];
  std::ifstream archivo;
  archivo.open(nombre.c_str());
  if(!archivo.is_open())
      return false;
  
  while(!archivo.eof()){
    archivo.getline(buffer,199);
    codigo+=buffer;
    codigo += "\n";
  }
  
  std::cout << "CODIGO: \n" << codigo << "FINCODIGO\n";
  const char* string=codigo.c_str();
  glShaderSource(shader, 1, &string,NULL);
  glCompileShader(shader);
  
  int compilado=0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compilado);
  if(!compilado){
   std::cout << "NO COMPILA\n"; 
  }
  
  return compilado;
}

bool FragmentShader::cargarDesdeArchivo(std::string nombre){
  return Shader::cargarDesdeArchivo(nombre, GL_FRAGMENT_SHADER);
}
bool VertexShader::cargarDesdeArchivo(std::string nombre){
  return Shader::cargarDesdeArchivo(nombre, GL_VERTEX_SHADER);
}

std::string Shader::getInfoLog(){
  std::vector<char> log;
  log.reserve(500);
  int longitud;
  glGetShaderInfoLog(shader, 500, &longitud, &log[0]);
  std::string retorno(&log[0]);  
  return retorno;
}

GLint Shader::getId(){
  return shader;
}
