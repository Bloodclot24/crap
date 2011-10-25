#include "Cubo.h"
#include "GL/gl.h"

Cubo::Cubo(){
}

void Cubo::cuadradoMedio(){
  glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    float incremento = 0.05;
	for (float incy = 0; incy < 1; incy += incremento)
		for (float incx = 0; incx < 1; incx += incremento) {
			glTexCoord2f(1 - incy, 1 - incx);
			glVertex3f(-0.5 + incx, -0.5 + incy, 0.5);
			glTexCoord2f(1 - incremento - incy, 1 - incx);
			glVertex3f(-0.5 + incx, -0.5 + incremento + incy, 0.5);
			glTexCoord2f(1 - incremento - incy, 1 - incremento - incx);
			glVertex3f(-0.5 + incremento + incx, -0.5 + incremento + incy, 0.5);
			glTexCoord2f(1 - incy, 1 - incremento - incx);
			glVertex3f(-0.5 + incremento + incx, -0.5 + incy, 0.5);
		}

   glNormal3f(0,0,-1);
   for(float incy=0; incy < 1; incy += incremento)
   	for(float incx=0; incx < 1; incx += incremento){
   		glTexCoord2f(1 - incy, 1 - incx);
			glVertex3f(-0.5 + incx, -0.5 + incy,-0.5);
			glTexCoord2f(1 - incremento - incy, 1 - incx);
			glVertex3f(-0.5 + incx, -0.5 + incremento + incy,-0.5);
			glTexCoord2f(1 - incremento - incy, 1 - incremento - incx);
			glVertex3f(-0.5 + incremento + incx, -0.5 + incremento + incy,-0.5);
			glTexCoord2f(1 - incy, 1 - incremento - incx);
			glVertex3f(-0.5 + incremento + incx, -0.5 + incy,-0.5);
   	}

  glNormal3f(-1,0,0);
  for(float incy=0; incy < 1; incy += incremento)
  	for(float incx=0; incx < 1; incx += incremento){
  		glTexCoord2f(1 - incy, 1 - incx);
			glVertex3f(-0.5,-0.5 + incx, -0.5 + incy);
			glTexCoord2f(1 - incremento - incy, 1 - incx);
			glVertex3f(-0.5,-0.5 + incx, -0.5 + incremento + incy);
			glTexCoord2f(1 - incremento - incy, 1 - incremento - incx);
			glVertex3f(-0.5,-0.5 + incremento + incx, -0.5 + incremento + incy);
			glTexCoord2f(1 - incy, 1 - incremento - incx);
			glVertex3f(-0.5,-0.5 + incremento + incx, -0.5 + incy);
  	}

  glNormal3f(1,0,0);
  for(float incy=0; incy < 1; incy += incremento)
  	for(float incx=0; incx < 1; incx += incremento){
  		glTexCoord2f(1 - incy, 1 - incx);
			glVertex3f(0.5,-0.5 + incx, -0.5 + incy);
			glTexCoord2f(1 - incremento - incy, 1 - incx);
			glVertex3f(0.5,-0.5 + incx, -0.5 + incremento + incy);
			glTexCoord2f(1 - incremento - incy, 1 - incremento - incx);
			glVertex3f(0.5,-0.5 + incremento + incx, -0.5 + incremento + incy);
			glTexCoord2f(1 - incy, 1 - incremento - incx);
			glVertex3f(0.5,-0.5 + incremento + incx, -0.5 + incy);
  	}

  glNormal3f(0,-1,0);
  for(float incy=0; incy < 1; incy += incremento)
  	for(float incx=0; incx < 1; incx += incremento){
  		glTexCoord2f(1 - incy, 1 - incx);
			glVertex3f(-0.5 + incx,-0.5, -0.5 + incy);
			glTexCoord2f(1 - incremento - incy, 1 - incx);
			glVertex3f(-0.5 + incx,-0.5, -0.5 + incremento + incy);
			glTexCoord2f(1 - incremento - incy, 1 - incremento - incx);
			glVertex3f(-0.5 + incremento + incx,-0.5, -0.5 + incremento + incy);
			glTexCoord2f(1 - incy, 1 - incremento - incx);
			glVertex3f(-0.5 + incremento + incx,-0.5, -0.5 + incy);
  	}

  glNormal3f(0,1,0);
  for(float incy=0; incy < 1; incy += incremento)
  	for(float incx=0; incx < 1; incx += incremento){
  		glTexCoord2f(1 - incy, 1 - incx);
			glVertex3f(-0.5 + incx,0.5, -0.5 + incy);
			glTexCoord2f(1 - incremento - incy, 1 - incx);
			glVertex3f(-0.5 + incx,0.5, -0.5 + incremento + incy);
			glTexCoord2f(1 - incremento - incy, 1 - incremento - incx);
			glVertex3f(-0.5 + incremento + incx,0.5, -0.5 + incremento + incy);
			glTexCoord2f(1 - incy, 1 - incremento - incx);
			glVertex3f(-0.5 + incremento + incx,0.5, -0.5 + incy);
  	}
  	glEnd();
}
//glNormal3f(normalx,normaly,normalz);
// float incremento = 0.05;
// for (float incz = 0; incz < 1 && normalz == 0; incz += incremento*normalz)
//	for (float incy = 0; incy < 1; incy += incremento)
//		for (float incx = 0; incx < 1; incx += incremento) {
//			glTexCoord2f(1 - incy, 1 - incx);
//			glVertex3f((-0.5 + incx)*(1 - abs(normalx)) + 0.5*normalx, (-0.5 + incy)*(1 - abs(normaly)) + 0.5*normaly, (-0.5 + incz)*(1 - abs(normalz)) + 0.5*normalz);

void Cubo::do_dibujar() {
	cuadradoMedio();
}
