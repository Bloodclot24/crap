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

void ComandoCambiarTextura::cargarTextura3D( const char * filename ){
 /*   int width, height;
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

	// Typical cube map settings
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, data );

    free( data );
*/

	   int width, height;
	    unsigned char * data;
	    glActiveTexture(GL_TEXTURE0);
		GLuint texID;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
		const char * suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
		GLuint targets[] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
	    width = 512;
	    height = 512;
	    data = (unsigned char *)malloc( width * height * 3 );

		FILE * file;
		string name;

		for (int i = 0; i < 6; i++) {
			name = string(filename) + "_" + suffixes[i] + ".png";
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
