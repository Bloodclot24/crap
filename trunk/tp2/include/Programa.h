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
};

#endif
