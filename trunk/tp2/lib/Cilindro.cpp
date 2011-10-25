#include "Cilindro.h"
#include <GL/glut.h>
#include <math.h>

Cilindro::Cilindro(){
}

void Cilindro::dibujarCirculo(int segmentos, float radio, float z){

	float inc = 0.1;
	float incremento = inc;
    glBegin(GL_TRIANGLE_FAN);
    if(z>0)
    	glNormal3f(0, 0, 1);
    else
    	glNormal3f(0, 0, -1);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0, 0, z);
    for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos) {
    	glTexCoord2f(0.5 + cos(i)*radio*incremento, 0.5 + sin(i)*radio*incremento);//ojo normalizar para que radio pueda ser distinto de 0.5
    	glVertex3f(cos(i)*radio*incremento, sin(i)*radio*incremento, z);
    }
    glEnd();

	glBegin(GL_TRIANGLE_STRIP);//ojo normal
	for (; incremento < 1; incremento += inc)
		for (float i = 0; i <= 2 * M_PI; i += 2 * M_PI / segmentos) {
			float _cos = cos(i)*radio;
			float _sin = sin(i)*radio;
		   	glTexCoord2f(0.5 + _cos*incremento, 0.5 + _sin*incremento);//ojo normalizar para que radio pueda ser distinto de 0.5
		    glVertex3f(_cos*incremento, _sin*incremento, z);
		   	glTexCoord2f(0.5 + _cos*(incremento+inc), 0.5 + _sin*(incremento+inc));//ojo normalizar para que radio pueda ser distinto de 0.5
		    glVertex3f(_cos*(incremento+inc),_sin*(incremento+inc), z);
		}
	glEnd();
}

void Cilindro::do_dibujar() {
	int segmentos = 42;
	glPushMatrix();
	glRotatef(60,0,1,1);
	glBegin(GL_TRIANGLE_STRIP);
	float radio = 0.5;
	float inc = 0.1;
	for (float incremento = 0; incremento < 1; incremento += inc)
		for (float i = 0; i <= 2 * M_PI; i += 2 * M_PI / segmentos) {
			float _cos = cos(i)*radio;
			float _sin = sin(i)*radio;
			glNormal3f(_cos, _sin, 0);
			glTexCoord2f(1 - i / (2 * M_PI), incremento);
			glVertex3f(_cos, _sin, -0.5 + incremento);
			glTexCoord2f(1 - i / (2 * M_PI), inc + incremento);
			glVertex3f(_cos, _sin, -0.5 + inc + incremento);
		}
	glEnd();

	//Dibujo las tapas
	dibujarCirculo(segmentos, radio, 0.5);
	dibujarCirculo(segmentos, radio, -0.5);
	glPopMatrix();
}

