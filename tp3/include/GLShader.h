#ifndef _GLSHADER_H_
#define _GLSHADER_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <map>
#include <string>

class GLShader
{

    static std::map<std::string, GLuint> vshaders;
    static std::map<std::string, GLuint> fshaders;
    static std::map<std::string, GLuint> programs;

    GLShader();

    static GLuint getFShader(std::string alias);
    static GLuint getVShader(std::string alias);

    public:
    static void loadVShader(std::string fileName, std::string alias);
    static void loadFShader(std::string fileName, std::string alias);
    static void createProgram(std::string name, std::string vshader, std::string fshader);
    static void useProgram(std::string alias);
};

#endif /* _GLSHADER_H_ */
