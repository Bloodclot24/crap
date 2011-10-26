#include "ComandoCambiarTextura.h"
#include "MundoTP2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

ComandoCambiarTextura::ComandoCambiarTextura(const char * filename){
 cargarTextura(filename);
}

void ComandoCambiarTextura::ejecutar(){
  MundoTP2::get_instance()->obtenerCuerpo()->setColor(1,1,1);
  MundoTP2::get_instance()->obtenerCuerpo()->setTextura(texture);
}

GLuint ComandoCambiarTextura::getTextura(){
	return texture;
}
void ComandoCambiarTextura::cargarTextura( const char * filename ){
    int width, height;
    unsigned char * data;

    FILE * file;
    file = fopen( filename, "rb" );

    width = 1024;
    height = 512;
    data = (unsigned char *)malloc( width * height * 3 );

    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, data );

    free( data );
}


