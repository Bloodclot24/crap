#include "Cilindro.h"
#include <GL/glut.h>
#include <math.h>

Cilindro::Cilindro(){
}

void Cilindro::dibujarCirculo(int segmentos, float z){

    glBegin(GL_TRIANGLE_FAN);
    if(z>0)
    	glNormal3f(0, 0, 1);
    else
    	glNormal3f(0, 0, -1);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0, 0, z);
    for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos) {
    	glTexCoord2f(1-(cos(i) + 1)/2, (sin(i) + 1 )/2);
    	glVertex3f(cos(i), sin(i), z);
    }
    glEnd();
}

void Cilindro::do_dibujar() {
	glBindTexture (GL_TEXTURE_2D, texture);
	int segmentos = 30;
	glPushMatrix();
	glRotatef(60,0,1,1);
	glScalef(0.4,0.4,1);
	glBegin(GL_TRIANGLE_STRIP);
	float inc = 0.1;
	for(float incremento = 0; incremento < 1; incremento += inc)
	for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos){
	    float _cos = cos(i);
	    float _sin = sin(i);
	    glNormal3f(_cos, _sin, 0);
	    glTexCoord2f(1 - i/(2*M_PI),incremento);
	    glVertex3f(_cos, _sin, -0.5 + incremento);
	    glTexCoord2f(1 - i/(2*M_PI), inc + incremento);
	    glVertex3f(_cos, _sin, -0.5 + inc + incremento);
	}
	glEnd();

	//Dibujo las tapas
	glPushMatrix();
//	glTranslatef(0, 0, 0.5);
	glScalef(1, 1, 1);
	dibujarCirculo(segmentos, 0.5);
	glPopMatrix();

	glPushMatrix();
//	glTranslatef(0, 0, -0.5);
//	glRotatef(180, 1, 0, 0);
	dibujarCirculo(segmentos,-0.5);
	glPopMatrix();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);
}

