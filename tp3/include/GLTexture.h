#ifndef _GLTEXTURE_H_
#define _GLTEXTURE_H_

#include <map>
#include <string>

#include "GL/gl.h"
#include "GL/glu.h"

class GLTexture
{

    static std::map<std::string, GLuint> textures;

    GLTexture();
    public:

    static void load(std::string fileName, std::string alias);
    static void bind(std::string textureAlias);
    static void unbind();
};

#endif /* _GLTEXTURE_H_ */
