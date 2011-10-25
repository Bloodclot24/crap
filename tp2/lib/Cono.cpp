#include "Cono.h"
#include <GL/glut.h>
#include <math.h>

Cono::Cono(){
}

void Cono::dibujarCirculo(int segmentos, float radio, float z){ //se podria usar para los laterales ojo con la textura

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

void Cono::do_dibujar() {
	int segmentos = 30;
	float radio = 0.5;
	glPushMatrix();
	float inc = 0.01;
	glBegin(GL_QUADS);
	for (float incremento = 0; incremento < 1; incremento += inc)
		for (float i = 0; i <= 2 * M_PI; i += 2 * M_PI / segmentos) {
			float _cos = cos(i)*radio;
			float _sin = sin(i)*radio;
			float _cosi = cos(i + 2 * M_PI / segmentos)*radio;
			float _sini = sin(i + 2 * M_PI / segmentos)*radio;
			glTexCoord2f(1 - i / (2 * M_PI), incremento);
		    glVertex3f(_cos*incremento, _sin*incremento, 0.5 - incremento);
		    glTexCoord2f(1 - i / (2 * M_PI), inc + incremento);
		    glVertex3f(_cos*(incremento+inc), _sin*(incremento+inc), 0.5 - (incremento+inc));
		    glTexCoord2f(1 - (i+ 2 * M_PI / segmentos) / (2 * M_PI), inc + incremento);
		    glVertex3f(_cosi*(incremento+inc), _sini*(incremento+inc), 0.5 - (incremento+inc));
		    glTexCoord2f(1 - (i+ 2 * M_PI / segmentos) / (2 * M_PI), incremento);
		    glVertex3f(_cosi*incremento, _sini*incremento, 0.5 - incremento);
		}
	glEnd();

	//Dibujo la tapa
	dibujarCirculo(segmentos, radio, -0.5);
	glPopMatrix();
}

