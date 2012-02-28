#include "Primitive.h"

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
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);

    std::string upperAlias = alias;
    std::transform(upperAlias.begin(), upperAlias.end(), upperAlias.begin(), ::toupper);

    textures[upperAlias] = textureId;
}


void GLTexture::createCube(std::string alias)
{
    GLuint cubeTexture;
    glGenTextures(1, &cubeTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int width = 512;
    int height = 512;


    for(int i = 0; i < 6; ++i){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8,
                     width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


    std::string upperAlias = alias;
    std::transform(upperAlias.begin(), upperAlias.end(), upperAlias.begin(), ::toupper);

    textures[upperAlias] = cubeTexture;
}

void GLTexture::beginRenderToCube(std::string alias, int face)
{
    std::string upperAlias = alias;
    std::transform(upperAlias.begin(), upperAlias.end(), upperAlias.begin(), ::toupper);

    GLuint cubeTexture = textures[upperAlias];

    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, cubeTexture, 0);

    GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

    if(status != GL_FRAMEBUFFER_COMPLETE)
        printf("Status error: %08x\n", status);
}

void GLTexture::endRenderToCube()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GLTexture::bindCubic(std::string textureAlias)
{
    glEnable(GL_TEXTURE_CUBE_MAP);
    std::string upperAlias = textureAlias;
    std::transform(upperAlias.begin(), upperAlias.end(), upperAlias.begin(), ::toupper);

    if(!textures.count(upperAlias)){
        printf("Textura inexistente (%s)\n", upperAlias.c_str());
        exit(-1);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, textures[upperAlias]);
}

void GLTexture::bind(std::string textureAlias)
{
    glEnable(GL_TEXTURE_2D);
    std::string upperAlias = textureAlias;
    std::transform(upperAlias.begin(), upperAlias.end(), upperAlias.begin(), ::toupper);

    if(!textures.count(upperAlias)){
        printf("Textura inexistente (%s)\n", upperAlias.c_str());
        exit(-1);
    }

    glBindTexture(GL_TEXTURE_2D, textures[upperAlias]);    
}

void GLTexture::unbind()
{
    glDisable(GL_TEXTURE_2D);
}
