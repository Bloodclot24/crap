#include "GLTexture.h"

#include <vector>
#include <stdio.h>

#include <algorithm>

std::map<std::string, GLuint> GLTexture::textures;

GLTexture::GLTexture()
{
}

void GLTexture::load(std::string fileName, std::string alias)
{
    int width, height;
    std::vector<char> data;
    GLuint textureId;

    FILE * file = fopen(fileName.c_str(), "rb" );
    width = 1024;
    height = 512;

    data.reserve(width * height * 3);

    fread(&data[0], width * height * 3, 1, file );

    fclose(file);

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);

//	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);

    std::string upperAlias = alias;
    std::transform(upperAlias.begin(), upperAlias.end(), upperAlias.begin(), ::toupper);

    textures[upperAlias] = textureId;
}

void GLTexture::bind(std::string textureAlias)
{
    std::string upperAlias = textureAlias;
    std::transform(upperAlias.begin(), upperAlias.end(), upperAlias.begin(), ::toupper);

    glBindTexture(GL_TEXTURE_2D, textures[upperAlias]);    
}

void GLTexture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
