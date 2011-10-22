#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

class Shader{
private:
  GLuint shader;
  GLuint program;
  
public:
  Shader();
  bool cargarDesdeArchivo(std::string nombre);
  std::string getInfoLog();
  GLuint getProgram();
};

#endif
