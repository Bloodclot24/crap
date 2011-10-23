#include "Toroide.h"
#include <GL/glut.h>
#include <math.h>

Toroide::Toroide(){
	cargarTextura("earth.raw");
}

void Toroide::do_dibujar(){
	glBindTexture (GL_TEXTURE_2D, texture);
	glEnable(GL_NORMALIZE);
	glPushMatrix();
	glRotatef(90, 1,0,0);
	glScalef(0.1,0.1,0.1);
	float incremento=6;
	for(float angulo = 0; angulo < 360; angulo +=incremento){
		glPushMatrix();
		glRotatef(angulo, 0,1,0);
		glTranslatef(4,0,0);
		int segmentosAnillo = 30;

		glBegin(GL_TRIANGLE_STRIP);
		for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentosAnillo){
		    float _cos = cos(i);
		    float _sin = sin(i);
		    glNormal3f(_cos, _sin, 0);
		    glTexCoord2f(angulo/360,1 - i/(2*M_PI) + 0.5);
		    glVertex3f(_cos, _sin, -(_cos + 4)*tan(incremento/2*M_PI/180));
		    glTexCoord2f((angulo - incremento)/360 ,1 - i/(2*M_PI)+ 0.5);
		    glVertex3f(_cos, _sin, (_cos + 4)*tan(incremento/2*M_PI/180));
		}
		glEnd();

		glPopMatrix();
	}
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);
}
