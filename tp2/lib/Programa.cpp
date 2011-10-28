#include "Programa.h"
#include <vector>
#include <sstream>

std::map<std::string, Programa*> Programa::programas;

Programa* Programa::crearPrograma(std::list< VertexShader > vss, std::list< FragmentShader > fss){
  std::string id;
  std::stringstream out;
    
  std::list<VertexShader>::iterator itv;
  for(itv=vss.begin(); itv != vss.end(); itv++){
   out << itv->getId();
  }
  std::list<FragmentShader>::iterator itf;
  for(itf=fss.begin(); itf != fss.end(); itf++){
   out << itf->getId();
  }
  id = out.str();
  if(programas[id] == NULL)
     programas[id] = compilarPrograma(vss, fss);
  return programas[id];
}

Programa* Programa::compilarPrograma(std::list< VertexShader > vss, std::list< FragmentShader > fss){
  GLint program = glCreateProgram();
  
  if(vss.size() == 0 || fss.size() == 0)
     return NULL;
  
  std::cout << "Compilar shaders con:\n";
  
  std::list<VertexShader>::iterator itv;
  for(itv=vss.begin(); itv != vss.end(); itv++){
    std::cout << "VSHADER: " << itv->getId() << "\n";
    glAttachShader(program, itv->getId());
  }
  
  std::list<FragmentShader>::iterator itf;
  for(itf=fss.begin(); itf != fss.end(); itf++){
    std::cout << "FSHADER: " << itf->getId() << "\n";
    glAttachShader(program, itf->getId()); 
  }
  
  glLinkProgram(program);
  
  int linkeado=0;
  glGetProgramiv(program, GL_LINK_STATUS, &linkeado);
  if(!linkeado){
    std::cout << "Error al linkear el programa.\n";
    mostrarLog(program);
    glDeleteProgram(program);
    return NULL;
  }
  else{
    std::cout << "Programa "<< program <<" linkeado correctamente\n";
    Programa *p = new Programa;
    p->idPrograma = program;
    return p;
  }
}

void Programa::mostrarLog(GLuint program){
  std::vector<char> log;
  log.reserve(500);
  int longitud;
  glGetShaderInfoLog(program, 500, &longitud, &log[0]);
  std::string texto(&log[0]);
  std::cout << "LOG: " << texto.c_str() << "\n";
}

void Programa::usar(){
   glUseProgram(idPrograma);
}



void Programa::cambiarUniforme(const char* nombre, GLfloat valor){
  if(idPrograma == 0)
    return;

  GLint id = glGetUniformLocation(idPrograma, nombre);
  if(id == -1){
   return; 
  }
  
  glUniform1f(id, valor);
}

void Programa::cambiarUniformeVec3(const char* nombre, GLfloat valor[3]){
  if(idPrograma == 0)
    return;

  GLint id = glGetUniformLocation(idPrograma, nombre);
  if(id == -1){
   return; 
  }
  
  glUniform3fv(id, 1, valor);
}

void Programa::cambiarUniforme(const char* nombre, GLfloat valor[16]){
  if(idPrograma == 0)
    return;

  GLint id = glGetUniformLocation(idPrograma, nombre);
  if(id == -1){
   return; 
  }
  
  glUniformMatrix4fv(id, 1, false, valor);
}

void Programa::cambiarUniforme1i(const char* nombre, GLint valor){
  if(idPrograma == 0)
    return;

  GLint id = glGetUniformLocation(idPrograma, nombre);
  if(id == -1){
   return; 
  }
  
  glUniform1i(id, valor);
}