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
    std::string cubemapPaths[6] = {filename"_positive_x.png", filename"_negative_x.png", filename"_positive_y.png",
    		filename"_negative_y.png", filename"_positive_z.png", filename"_negative_z.png"};

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
        ilLoadImage(cubemapPaths[i].c_str());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
          ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
    }


/*
	int width, height;
    unsigned char * data;
    glActiveTexture(GL_TEXTURE0);
    GLuint texID;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    const char * suffixes[] = { "positive_x", "negative_x", "positive_y", "negative_y", "positive_z", "negative_z" };
    GLuint targets[] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                         GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                         GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                         GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
                       };
    width = 512;
    height = 512;
    data = (unsigned char *)malloc( width * height * 3 );

    FILE * file;

    for (int i = 0; i < 6; i++) {
        string name = string(filename) + "_" + suffixes[i] + ".png.raw";
        file = fopen(name.c_str(), "rb" );

        fread( data, width * height * 3, 1, file );

        fclose( file );

        gluBuild3DMipmaps(GL_TEXTURE_CUBE_MAP, 3, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data );

    }

    free( data );
    //   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // Typical cube map settings
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
*/
    /*

    glActiveTexture(GL_TEXTURE0);
        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
        const char * suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
        GLuint targets[] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    		    GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    		    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    		    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
        for (int i = 0; i < 6; i++) {
    	    string texName = string("cubo") + "_" + suffixes[i] + ".png";
    	    QImage img = QGLWidget::convertToGLFormat(QImage(texName.c_str(), "PNG"));
    	    glTexImage2D(targets[i], 0, GL_RGBA, img.width(), img.height(), 0,
    			    GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
        }
        // Typical cube map settings
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // Set the CubeMapTex uniform to texture unit 0
    /*	uniloc = glGetUniformLocation(programHandle, "CubeMapTex");
        if (uniloc >= 0)
    	    glUniform1i(uniloc, 0);
    */
}
