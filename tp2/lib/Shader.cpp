#include "Shader.h"
#include <fstream>
#include <vector>

Shader::Shader(){
    shader = 0;
    program = 0;
}

bool Shader::cargarDesdeArchivo(std::string nombre){
  shader = glCreateShader(GL_VERTEX_SHADER);
  std::string codigo;
  char buffer[100];
  std::ifstream archivo;
  archivo.open(nombre.c_str());
  while(!archivo.eof()){
    archivo.getline(buffer,99);
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
  program = glCreateProgram();
  glAttachShader(program, shader);
  glLinkProgram(program);
  
  int linkeado=0;
  glGetShaderiv(shader, GL_LINK_STATUS, &linkeado);
  if(!linkeado){
    std::cout << "NO LINKEA\n"; 
  }
  return compilado+linkeado;
}

std::string Shader::getInfoLog(){
  std::vector<char> log;
  log.reserve(500);
  int longitud;
  glGetShaderInfoLog(shader, 500, &longitud, &log[0]);
  std::string retorno(&log[0]);
  
  glValidateProgram(program);
  int resultado=0;
  glGetShaderiv(shader, GL_VALIDATE_STATUS, &resultado);
  std::cout << "Valido: " << resultado << "\n";
  
  int maxLength=0;
  glGetProgramiv(program,GL_INFO_LOG_LENGTH,&maxLength);
  log.reserve(maxLength);
  std::cout << "INFOLOG LEN: " << maxLength << "\n";
  glGetProgramInfoLog(program, maxLength, &longitud, &log[0]);
  retorno += &log[0];
  
  
  
  return retorno;
}

GLuint Shader::getProgram(){
  return program;
}
