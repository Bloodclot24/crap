#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

class Shader{
private:
  GLuint shader;
  
protected:
  Shader();
  virtual bool cargarDesdeArchivo(std::string nombre, GLenum tipo);
public:
  virtual std::string getInfoLog();
  GLint getId();
};

class VertexShader:public Shader{
public:
  bool cargarDesdeArchivo(std::string nombre);
};

class FragmentShader:public Shader{
public:
  bool cargarDesdeArchivo(std::string nombre);
};

#endif
