#include "MundoTP2.h"
#include <iostream>
#include "Cubo.h"
#include "Esfera.h"
#include "Toroide.h"
#include "ComandoCambiarColor.h"
#include "ComandoCambiarForma.h"

MundoTP2* MundoTP2::te_odio2 = NULL;

MundoTP2::MundoTP2(){
  figura=new Cubo();
  resetearRotacion();
}

void MundoTP2::crearMenues(){
  Cuerpo* c;
  c=new Esfera();
  c->setColor(1,0,0);
  menuTexturas.agregarElemento(c, new ComandoCambiarColor(1,0,0));

  c=new Esfera();
  c->setColor(0,1,0);
  menuTexturas.agregarElemento(c, new ComandoCambiarColor(0,1,0));

  c=new Esfera();
  c->setColor(0,0,1);
  menuTexturas.agregarElemento(c, new ComandoCambiarColor(0,0,1));
  
  menuFormas.cambiarOrientacion(MENU_VERTICAL);
  c=new Esfera();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaEsfera());
  c=new Cubo();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaCubo());
  c=new Toroide();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaToroide());
  
}

void MundoTP2::inicializar(){
  glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0); 
  GLfloat light_position[] = { 5.0, 5.0, 10.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  crearMenues();
}

void MundoTP2::vistaOrtogonal(){
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho(-(float)ancho_ventana/alto_ventana,(float)ancho_ventana/alto_ventana,-1,1,-30,30);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0,0,2,0,0,0,0,1,0);
}

void MundoTP2::vistaPerspectiva(){
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (GLfloat)ancho_ventana/(GLfloat)alto_ventana, 0.10, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0,0,2,0,0,0,0,1,0);
}

void MundoTP2::display(){
  glViewport (0, 0, (GLsizei) ancho_ventana, (GLsizei) alto_ventana);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Menues
  vistaOrtogonal();
  glPushMatrix();
  glTranslatef(0,0.8,-0.5);
  menuTexturas.dibujar();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-0.8*(float)ancho_ventana/alto_ventana,0,-0.5);
  menuFormas.dibujar();
  glPopMatrix();
  
  //Objeto central
  vistaPerspectiva();
  glColor3f(1,0,0);
  glTranslatef(0,-0.25,0);
  glRotatef(rotX, 1,0,0);
  glRotatef(rotY, 0,1,0);
  glRotatef(rotZ, 0,0,1);
  figura->dibujar();
  
  glutSwapBuffers();
}

void MundoTP2::mouse(int button, int state, int x, int y){
  std::cout << "Click b: " << button << " s: " << state << " x: " << x << " y: " << y << "\n";
 
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    menuTexturas.click(x,y+0.8*alto_ventana);
    menuFormas.click(x+0.8*(float)ancho_ventana/alto_ventana,y);
  }
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

void MundoTP2::cambiarFigura(Cuerpo* cuerpo){
  figura=cuerpo;
}

void MundoTP2::resetearRotacion(){
 rotX=rotY=rotZ=0; 
}

Cuerpo* MundoTP2::obtenerCuerpo(){
 return figura; 
}


MundoTP2::~MundoTP2(){
 delete figura; 
}
