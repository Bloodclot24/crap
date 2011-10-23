#include "Cuerpo.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

void Cuerpo::dibujar(){
 //poner shaders
 //estado de animación
 glColor3f(r,g,b);
 glUseProgram(vertexShader.getProgram());
 do_dibujar();
}

float Cuerpo::getAlto(){
  return alto;
}

float Cuerpo::getAncho(){
  return ancho;
}

Cuerpo::Cuerpo(){
    alto=1;
    ancho=1;
    r=g=b=0.5;
}

void Cuerpo::setColor(float r, float g, float b){
  this->r=r;
  this->g=g;
  this->b=b;
  
}

void Cuerpo::setVertexShader(Shader s){
  vertexShader = s;
}

void Cuerpo::cargarTextura( const char * filename )
{
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

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

    free( data );
}
