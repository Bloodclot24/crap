#include "Cuerpo.h"
#include <GL/gl.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

void Cuerpo::dibujar(){
 glColor3f(r,g,b);
  
 //glUseProgram(vertexShader.getProgram());
 if(vs.getId() != 0){
  GLint program = glCreateProgram();
  glAttachShader(program, vs.getId());
  glAttachShader(program, fs.getId());
  glLinkProgram(program);
  glUseProgram(program);
  std::vector<char> log;
  log.reserve(500);
  int longitud;
  glGetShaderInfoLog(program, 500, &longitud, &log[0]);
  std::string retorno(&log[0]);  
  std::cout << "LOGLINK: " << retorno << "\n";
 }
 
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

void Cuerpo::setShader(VertexShader vs){
  this->vs = vs;
}

void Cuerpo::setShader(FragmentShader fs){
  this->fs =fs;
}

void Cuerpo::cargarTextura( const char * filename ){
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

