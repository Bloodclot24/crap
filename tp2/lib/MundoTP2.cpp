#include "MundoTP2.h"
#include <iostream>

MundoTP2::MundoTP2(){

}

void MundoTP2::display(){
  std::cout << "Soy el mundo 2\n"; 
  glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST); 
  glViewport (0, 0, (GLsizei) ancho_ventana, (GLsizei) alto_ventana); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (GLfloat) ancho_ventana/(GLfloat) alto_ventana, 0.10, 100.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ///////////////////////////////////////////////////
  // Escena 3D
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt (5,5,5,0,0,0, 0,0,1);
  glutSwapBuffers();

}

Mundo* MundoTP2::get_instance(){
  if(te_odio == NULL)
    te_odio=new MundoTP2();
    
  return te_odio;
}