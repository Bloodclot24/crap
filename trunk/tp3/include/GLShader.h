#ifndef _GLSHADER_H_
#define _GLSHADER_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <map>
#include <string>
#include <stack>

class GLShader
{

    static std::map<std::string, GLuint> vshaders;
    static std::map<std::string, GLuint> fshaders;
    static std::map<std::string, GLuint> programs;
    static std::stack<std::string> stack;

    GLShader();

    static GLuint getFShader(std::string alias);
    static GLuint getVShader(std::string alias);

    static void useProgram(std::string alias);

    public:
    static void loadVShader(std::string fileName, std::string alias);
    static void loadFShader(std::string fileName, std::string alias);
    static void createProgram(std::string name, std::string vshader, std::string fshader);
    static void createProgram(std::string name, const char** vshaders, const char** fshaders);

    static void pushProgram(std::string alias);
    static void popProgram();

    static void setUniform(std::string name, float value);
};

#endif /* _GLSHADER_H_ */
