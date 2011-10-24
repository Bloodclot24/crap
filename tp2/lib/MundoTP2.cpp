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
#include "stdlib.h"

MundoTP2* MundoTP2::te_odio2 = NULL;

MundoTP2::MundoTP2(){
	figura = NULL;
	animando=false;
	x_mouse = 0;
	y_mouse = 0;
	mouse_capturado = false;
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
  if(!vshaderSimple.cargarDesdeArchivo("shaders/achatado.vert")){
    std::cout << "VLOG:" << vshaderSimple.getInfoLog() << "\n";
    exit(0);
  }
  
  VertexShader vshaderWtf;
  if(!vshaderWtf.cargarDesdeArchivo("shaders/simple.vert")){
    std::cout << "VLOG:" << vshaderWtf.getInfoLog() << "\n";
    exit(0);
  }
  
  FragmentShader fshaderSimple;
  if(!fshaderSimple.cargarDesdeArchivo("shaders/simple.frag")){
    std::cout << "FLOG:" << fshaderSimple.getInfoLog() << "\n";
    exit(0);
  }
  
  FragmentShader fshaderTextura;
  if(!fshaderTextura.cargarDesdeArchivo("shaders/textura.frag")){
    std::cout << "FLOG:" << fshaderTextura.getInfoLog() << "\n";
    exit(0);
  }
  c=new Esfera();
  c->agregarShader(vshaderSimple);
  c->agregarShader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarShader(vshaderSimple, fshaderTextura));

  c=new Esfera();
  c->agregarShader(vshaderWtf);
  c->agregarShader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarShader(vshaderWtf, fshaderTextura));
  
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
  figura=new Cubo();
  crearMenues();
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

void MundoTP2::motion(int x, int y) {
	if (mouse_capturado) {
		if (x_mouse < x)
			rotX += 1;
		else if(x_mouse > x)
				rotX -= 1;
		x_mouse = x;
		if (y_mouse < y)
			rotY += 1;
		else
			if(y_mouse > y)
				rotY -= 1;
		y_mouse = y;
		glutPostRedisplay();
		if (x_mouse < ancho_ventana / 3 || x_mouse > 2 * ancho_ventana / 3) {
			x_mouse = ancho_ventana / 2;
			glutWarpPointer(x_mouse, alto_ventana / 2);
		}
		if(y_mouse < alto_ventana / 3 || y_mouse > 2* alto_ventana / 3){
			y_mouse = alto_ventana / 2;
			glutWarpPointer(x_mouse, y_mouse);
		}
	}
}

void MundoTP2::capturar_mouse(){
	if(mouse_capturado){
		mouse_capturado = false;
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}
	else{
		mouse_capturado = true;
		glutSetCursor(GLUT_CURSOR_NONE);
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
    
	  desanimar(figura);
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

void MundoTP2::animame(Animable* animable, int milis){
  std::list<Animable*>::iterator itan;
  std::list<int>::iterator itmil;
  
  for(itan = animables.begin(), itmil = tiemposDeAnimacion.begin();
      itmil != tiemposDeAnimacion.end() && *itmil < milis;
      itmil++, itan++){}
      
  animables.insert(itan, animable);
  tiemposDeAnimacion.insert(itmil, milis);
  
  if(!animando){
    //poner timer
    glutTimerFunc(*(tiemposDeAnimacion.begin()), MundoTP2::static_timer_callback,0);
    animando=true;
  }
    
}

void MundoTP2::desanimar(Animable* animable){
  std::list<Animable*>::iterator itan;
  std::list<int>::iterator itmil;
  std::list<Animable*> nuevosAnimables;
  std::list<int> nuevosTiempos;
  
  for(itan = animables.begin(), itmil = tiemposDeAnimacion.begin();
      itmil != tiemposDeAnimacion.end();
      itmil++, itan++){
      if(*itan != animable){
	  nuevosTiempos.push_back(*itmil);
	  nuevosAnimables.push_back(*itan);
      }
  }
  animables = nuevosAnimables;
  tiemposDeAnimacion = nuevosTiempos;
}


void MundoTP2::timer_callback(){
  
  std::list<Animable*>::iterator itan;
  std::list<Animable*> nuevosAnimables;
  std::list<Animable*> animados;
  std::list<int>::iterator itmil;
  std::list<int> nuevosTiempos;
  int tiempo = *tiemposDeAnimacion.begin();
  
  for(itan = animables.begin(), itmil = tiemposDeAnimacion.begin();
      itmil != tiemposDeAnimacion.end();
      itmil++, itan++){
    
    int actual = *itmil-tiempo;
    if(actual<=0)
      animados.push_back(*itan);
    
    else{ 
	nuevosTiempos.push_back(actual);
	nuevosAnimables.push_back(*itan);
    }
  }
  
  animables = nuevosAnimables;
  tiemposDeAnimacion = nuevosTiempos;
  
  for(std::list<Animable*>::iterator it=animados.begin(); it!= animados.end(); it++)
      (*it)->animar();
  
  
  if(tiemposDeAnimacion.size() > 0){
    glutTimerFunc(*(tiemposDeAnimacion.begin()), MundoTP2::static_timer_callback,0);
  }
  else{
     animando=false;
  }
  glutPostRedisplay();
}

void MundoTP2::static_timer_callback(int ignorar){
  MundoTP2::get_instance()->timer_callback();
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
