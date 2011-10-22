#include "Toroide.h"
#include <GL/glut.h>
#include <math.h>

void Toroide::do_dibujar(){

	glEnable(GL_NORMALIZE);
	glPushMatrix();
	glRotatef(90, 1,0,0);
	glScalef(0.1,0.1,0.1);
	for(float angulo = 0; angulo < 360; angulo ++){
		glPushMatrix();
		glRotatef(angulo, 0,1,0);
		glTranslatef(4,0,0);
		int segmentosAnillo = 30;

		glBegin(GL_TRIANGLE_STRIP);
		for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentosAnillo){
		    float _cos = cos(i);
		    float _sin = sin(i);
		    glNormal3f(_cos, _sin, 0);
		    glVertex3f(_cos, _sin, -0.1);
		    glVertex3f(_cos, _sin, 0.1);
		}
		glEnd();

		glPopMatrix();
	}
	glPopMatrix();
}
