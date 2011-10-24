#include "Toroide.h"
#include <GL/glut.h>
#include <math.h>

Toroide::Toroide(){
}

void Toroide::do_dibujar(){
	glEnable(GL_NORMALIZE);
	glPushMatrix();
	glRotatef(90, 1,0,0);
	glScalef(0.1,0.1,0.1);
	float incremento=6;
	for(float angulo = 0; angulo < 360; angulo +=incremento){
		glPushMatrix();
		//glRotatef(angulo, 0,1,0);
		//glTranslatef(4,0,0);
		int segmentosAnillo = 30;

		glBegin(GL_TRIANGLE_STRIP);
		float angulor=angulo/180*M_PI;
		for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentosAnillo){
		    float _cos = cos(i);
		    float _sin = sin(i);
		    glNormal3f(_cos, _sin, 0);
		    glTexCoord2f(angulo/360,1 - i/(2*M_PI) + 0.5);
		    float x = 4+_cos;
		    float z = -(_cos + 4)*tan(incremento/2*M_PI/180);
		    glVertex3f(x*cos(angulor) + z*sin(angulor), _sin, -x*sin(angulor) + z*cos(angulor));
		    glTexCoord2f((angulo - incremento)/360 ,1 - i/(2*M_PI)+ 0.5);
		    z = -z;
		    glVertex3f(x*cos(angulor) + z*sin(angulor), _sin, -x*sin(angulor) + z*cos(angulor));
		   // glVertex3f(4 + _cos, _sin, (_cos + 4)*tan(incremento/2*M_PI/180));
		}
		glEnd();

		glPopMatrix();
	}
	glPopMatrix();
}
