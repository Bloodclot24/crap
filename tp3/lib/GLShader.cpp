#include "GLShader.h"

#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include <vector>

static void showLog(GLuint program){
  std::vector<char> log;
  log.reserve(500);
  int longitud;
  glGetShaderInfoLog(program, 500, &longitud, &log[0]);
  std::string texto(&log[0]);
  printf("%s", texto.c_str());
}

static std::string toUpper(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    return string;
}

static GLuint cargarDesdeArchivo(std::string name, GLenum type)
{
    GLuint shader = glCreateShader(type);

    std::string code;
    char buffer[200];
    std::ifstream file;
    file.open(name.c_str());

    if(!file.is_open()){
        printf("Archivo inexistente: %s\n", name.c_str());
        exit(-1);
    }
  
    while(!file.eof()){
        file.getline(buffer,199);
        code += buffer;
        code += "\n";
    }
  
    const char* codeString=code.c_str();
    glShaderSource(shader, 1, &codeString, NULL);
    glCompileShader(shader);

    int compiled=0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled){
        printf("El shader %s no compila.\n", name.c_str());
        showLog(shader);
        exit(-1);
    }

    return shader;
}

std::map<std::string, GLuint> GLShader::vshaders;
std::map<std::string, GLuint> GLShader::fshaders;
std::map<std::string, GLuint> GLShader::programs;
std::stack<std::string> GLShader::stack;

GLShader::GLShader()
{ 
}

void GLShader::loadVShader(std::string fileName, std::string alias)
{
    GLuint shader = cargarDesdeArchivo(fileName, GL_VERTEX_SHADER);
    vshaders[toUpper(alias)] = shader;
}

void GLShader::loadFShader(std::string fileName, std::string alias)
{
    GLuint shader = cargarDesdeArchivo(fileName, GL_FRAGMENT_SHADER);    
    fshaders[toUpper(alias)] = shader;
}

GLuint GLShader::getFShader(std::string alias)
{
    if(!fshaders.count(toUpper(alias))){
        printf("FShader inexistente (%s)\n", alias.c_str());
        exit(-1);
    }
     
    return fshaders[toUpper(alias)];
}

GLuint GLShader::getVShader(std::string alias)
{
    if(!vshaders.count(toUpper(alias))){
        printf("VShader inexistente (%s)\n", alias.c_str());
        exit(-1);
    }

    return vshaders[toUpper(alias)];
}

void GLShader::createProgram(std::string name, std::string vshader, std::string fshader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, getFShader(fshader));
    glAttachShader(program, getVShader(vshader));
    glLinkProgram(program);

    glUseProgram(program);

    int linked=0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if(!linked){
        printf("Error al linkear el programa.\n");
        showLog(program);
        glDeleteProgram(program);
    }
    else{
        printf("Programa %s (%d) linkeado correctamente\n", name.c_str(), program);
        programs[toUpper(name)] = program;
    }

}

void GLShader::useProgram(std::string alias)
{
    if(!programs.count(toUpper(alias))){
        printf("Programa inexistente (%s)\n", alias.c_str());
        exit(-1);
    }

    glUseProgram(programs[toUpper(alias)]);
}

void GLShader::pushProgram(std::string alias)
{
    stack.push(alias);
    useProgram(alias);
}

void GLShader::popProgram()
{
    stack.pop();
    useProgram(stack.top());
}


void GLShader::setUniform(std::string name, float value)
{

    GLint location = glGetUniformLocation(programs[toUpper(stack.top())], name.c_str());

    glUniform1f(location, value);
}
