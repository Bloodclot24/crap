#include "Shader.h"
#include <fstream>
#include <vector>

Shader::Shader(){
    shader = glCreateShader(GL_VERTEX_SHADER);
}

bool Shader::cargarDesdeArchivo(std::string nombre){
  std::string codigo;
  char buffer[100];
  std::ifstream archivo;
  archivo.open(nombre.c_str());
  std::cout << "Abierto\n";
  while(!archivo.eof()){
    archivo.getline(buffer,99);
    codigo+=buffer;
    codigo += "\n";
  }
  std::cout<< "Leido\n";
  std::cout << codigo << "\n";
  const char* string=codigo.c_str();
  glShaderSource(shader, 1, &string,NULL);
  glCompileShader(shader);
  int resultado=0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &resultado);
  return resultado;
}

std::string Shader::getInfoLog(){
  std::vector<char> log;
  log.reserve(500);
  int longitud;
  glGetShaderInfoLog(shader, 500, &longitud, &log[0]);
  std::string retorno(&log[0]);
  return retorno;
}