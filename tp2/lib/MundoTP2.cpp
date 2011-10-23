#include "MundoTP2.h"
#include <iostream>
#include "Cubo.h"
#include "Esfera.h"
#include "Toroide.h"
#include "Cilindro.h"
#include "Cono.h"
#include "ComandoCambiarColor.h"
#include "ComandoCambiarForma.h"
#include "ComandoCambiarShader.h"
#include "ComandoCambiarTextura.h"

MundoTP2* MundoTP2::te_odio2 = NULL;

MundoTP2::MundoTP2(){
	figura = NULL;
}


void MundoTP2::crearMenues(){
  Cuerpo* c;
  c=new Esfera();
  c->setColor(1,0,0);
  menuFragmentShader.agregarElemento(c, new ComandoCambiarColor(1,0,0));
  c=new Esfera();
  ComandoCambiarTextura* tierra = new ComandoCambiarTextura("earth.raw");
  c->setColor(1,1,1);
  c->setTextura(tierra->getTextura());
  menuFragmentShader.agregarElemento(c, tierra);
  c=new Esfera();
  c->setColor(1,1,1);
  ComandoCambiarTextura* ladrillo = new ComandoCambiarTextura("lad.raw");
  c->setTextura(ladrillo->getTextura());
  menuFragmentShader.agregarElemento(c, ladrillo);
  
  menuFormas.cambiarOrientacion(MENU_VERTICAL);
  c=new Esfera();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaEsfera());
  c=new Cubo();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaCubo());
  c=new Toroide();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaToroide());
  c=new Cilindro();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaCilindro());
  c=new Cono();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaCono());
  menuVertexShader.cambiarOrientacion(MENU_VERTICAL);
  
  VertexShader vshaderSimple;
  if(!vshaderSimple.cargarDesdeArchivo("shaders/textura.vert"))
    std::cout << "VLOG:" << vshaderSimple.getInfoLog() << "\n";
  
  VertexShader vshaderWtf;
  if(!vshaderWtf.cargarDesdeArchivo("shaders/wtf.vert"))
    std::cout << "VLOG:" << vshaderWtf.getInfoLog() << "\n";
  
  FragmentShader fshaderSimple;
  if(!fshaderSimple.cargarDesdeArchivo("shaders/textura.frag"))
    std::cout << "FLOG:" << fshaderSimple.getInfoLog() << "\n";
  c=new Esfera();
  c->agregarShader(vshaderSimple);
  c->agregarShader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarShader(vshaderSimple, fshaderSimple));

  c=new Esfera();
  c->agregarShader(vshaderWtf);
  c->agregarShader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarShader(vshaderWtf, fshaderSimple));
  
  c=new Esfera();
  VertexShader vshaderNulo;
  FragmentShader fshaderNulo;
  menuVertexShader.agregarElemento(c, new ComandoCambiarShader(vshaderNulo, fshaderNulo));

}

void MundoTP2::inicializar(){
  glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  GLfloat light_position[] = { 5.0, 5.0, 10.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  crearMenues();
  figura=new Cubo();
  resetearRotacion();

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
  menuFragmentShader.dibujar();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-0.8*(float)ancho_ventana/alto_ventana,0,-0.5);
  menuFormas.dibujar();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.8*(float)ancho_ventana/alto_ventana,0,-0.5);
  menuVertexShader.dibujar();
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
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    menuFragmentShader.click(x,y+0.8*alto_ventana);
    menuFormas.click(x+0.8*(float)ancho_ventana/alto_ventana,y);
    menuVertexShader.click(x-0.8*(float)ancho_ventana/alto_ventana,y);
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
  if(figura != NULL){
	  delete figura;
  }
  figura=cuerpo;
}

void MundoTP2::resetearRotacion(){
 rotX=rotY=rotZ=0; 
}

Cuerpo* MundoTP2::obtenerCuerpo(){
 return figura; 
}

void MundoTP2::destruirMenu(Menu menu) {

	std::vector<Cuerpo*> cuerpos = menu.getCuerpos();
	std::vector<Cuerpo*>::iterator it;
	for (it = cuerpos.begin(); it != cuerpos.end(); it++)
		delete *it;
	std::vector<Command*> comandos = menu.getComandos();
	std::vector<Command*>::iterator it1;
	for (it1 = comandos.begin(); it1 != comandos.end(); it1++)
		delete *it1;

}


void MundoTP2::destruir() {
 delete te_odio2;
}

MundoTP2::~MundoTP2() {
	if (figura != NULL)
		delete figura;
	destruirMenu(menuFormas);
	destruirMenu(menuVertexShader);
	destruirMenu(menuFragmentShader);

}
