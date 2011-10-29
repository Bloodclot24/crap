#include "ComandoCambiarTexturaCubica.h"
#include "MundoTP2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>>
#include <IL/il.h>


using namespace std;

ComandoCambiarTexturaCubica::ComandoCambiarTexturaCubica(const char * filename) {
    cargarTextura(filename);
}

void ComandoCambiarTexturaCubica::ejecutar() {
    MundoTP2::get_instance()->obtenerCuerpo()->setColor(1,1,1);
    MundoTP2::get_instance()->obtenerCuerpo()->setTexturaCubica(texture);
}

GLuint ComandoCambiarTexturaCubica::getTextura() {
    return texture;
}
void ComandoCambiarTexturaCubica::cargarTextura( const char * filename ) {

    ILuint ilTex;
    ilInit();
    std::string cubemapPaths[6] = {"_positive_x.png", "_negative_x.png", "_positive_y.png",
    		"_negative_y.png", "_positive_z.png", "_negative_z.png"};

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    for (int i = 0; i < 6; i++)
    {
        ilGenImages(1, &ilTex);
        ilBindImage(ilTex);
	std::string nombre = filename;
	nombre += cubemapPaths[i];
        ilLoadImage(nombre.c_str());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
          ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
    }
}
