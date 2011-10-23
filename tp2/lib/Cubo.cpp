#include "Cubo.h"
#include "GL/gl.h"

void Cubo::cuadradoMedio(){
  glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex2f(-0.5,-0.5);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1);
    glVertex2f(-0.5, 0.5);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
    glVertex2f( 0.5, 0.5);
    glNormal3f(0,0,1);
    glTexCoord2f(1,0);
    glVertex2f( 0.5,-0.5);
  glEnd();
}

void Cubo::do_dibujar(){

	cargarTextura("earth.raw");
	 glBindTexture (GL_TEXTURE_2D, texture);
  float angulos[4] = {0, 90, 180, 270};
  for(int i=0;i<4;i++){
    glPushMatrix();
      glRotatef(angulos[i], 1, 0, 0);
      glTranslatef(0,0,0.5);
      cuadradoMedio();
    glPopMatrix();
  }
  
  glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0,0,0.5);
    cuadradoMedio();
  glPopMatrix();
  
  glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    glTranslatef(0,0,0.5);
    cuadradoMedio();
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, NULL);
}
