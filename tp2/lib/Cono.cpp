#include "Cono.h"
#include <GL/glut.h>
#include <math.h>

Cono::Cono(){
}

void Cono::dibujarCirculo(int segmentos){

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0, 0, 0);
    for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos) {
    	glTexCoord2f(1-(cos(i) + 1)/2, (sin(i) + 1 )/2);
    	glVertex3f(cos(i), sin(i), 0);
    }
    glEnd();
}

void Cono::do_dibujar() {
	glBindTexture (GL_TEXTURE_2D, texture);
	int segmentos = 30;
	glPushMatrix();
	glRotatef(60,0,1,1);
	glScalef(0.4,0.4,1);
	glBegin(GL_TRIANGLE_STRIP);
	for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos){
	    float _cos = cos(i);
	    float _sin = sin(i);
	    glNormal3f(_cos, _sin, 0);
	    glTexCoord2f(1 - i/(M_PI),0);
	    glVertex3f(_cos, _sin, -0.5);
	    glTexCoord2f(1 - i/(M_PI),1);
	    glVertex3f(0,0, 0.5);
	}
	glEnd();

	//Dibujo la tapa
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glRotatef(180, 1, 0, 0);
	dibujarCirculo(segmentos);
	glPopMatrix();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);
}

