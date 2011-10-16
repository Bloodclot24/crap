#include "MundoTP2.h"
#include <iostream>
#include "Cubo.h"

MundoTP2* MundoTP2::te_odio2 = NULL;


MundoTP2::MundoTP2(){
  figura=new Cubo();
  resetearRotacion();
}

void MundoTP2::inicializar(){
  glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);  
}

void MundoTP2::display(){
  glViewport (0, 0, (GLsizei) ancho_ventana, (GLsizei) alto_ventana); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (GLfloat) ancho_ventana/(GLfloat) alto_ventana, 0.10, 100.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0,0,2,0,0,0,0,1,0);
  
  ///////////////////////////////////////////////////
  // Escena 3D
  glColor3f(1,0,0);
  glRotatef(rotX, 1,0,0);
  glRotatef(rotY, 0,1,0);
  glRotatef(rotZ, 0,0,1);
  figura->dibujar();
  
  glutSwapBuffers();
}

MundoTP2* MundoTP2::get_instance(){
  if(te_odio2 == NULL){
    te_odio2=new MundoTP2();
    te_odio = te_odio2;
  }
    
  return te_odio2;
}

void MundoTP2::rotarFigura(float angulo, bool x, bool y, bool z){
	if(x)
	  rotX+=angulo;
	if(y)
	  rotY+=angulo;
	if(z)
	  rotZ+=angulo;
}

void MundoTP2::resetearRotacion(){
 rotX=rotY=rotZ=0; 
}

MundoTP2::~MundoTP2(){
 delete figura; 
}
