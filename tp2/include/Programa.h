#ifndef PROGRAMA_H_INCLUDED
#define PROGRAMA_H_INCLUDED
#include "Shader.h"
#include <map>
#include <list>

class Programa{
private:
  static std::map<std::string, Programa*> programas;
  GLuint idPrograma;
  static Programa* compilarPrograma(std::list< VertexShader > vss, std::list< FragmentShader > fss);
  static void mostrarLog(GLuint program);
public:
  static Programa* crearPrograma(std::list<VertexShader> vss, std::list<FragmentShader> fss);
  void usar();
  void cambiarUniforme(const char* nombre, GLfloat valor);
  void cambiarUniforme(const char* nombre, GLfloat valor[16]);
  void cambiarUniformeVec3(const char* nombre, GLfloat valor[3]);
  void cambiarUniforme1i(const char* nombre, GLint valor);


};


#endif
