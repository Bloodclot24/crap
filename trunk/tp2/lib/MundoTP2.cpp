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
#include "ComandoCambiarTexturaCubica.h"
#include "ComandoCompuesto.h"
#include "stdlib.h"

MundoTP2* MundoTP2::te_odio2 = NULL;

MundoTP2::MundoTP2(){
	figura = NULL;
	animando=false;
	x_mouse = 0;
	y_mouse = 0;
	mouse_capturado = false;
	luz_1_encendida = true;
	luz_2_encendida = true;
	mostrar_menu = true;
}

void MundoTP2::crearMenues(){
  Cuerpo* c;
  menuFormas.cambiarOrientacion(MENU_VERTICAL);
  c=new Esfera();
  menuFormas.agregarElemento(c,new ComandoCambiarFormaEsfera());
  c=new Cubo();
  c->setRotacion(20,10,0);
  menuFormas.agregarElemento(c,new ComandoCambiarFormaCubo());
  c=new Toroide();
  c->setRotacion(40,20,0);
  menuFormas.agregarElemento(c,new ComandoCambiarFormaToroide());
  c=new Cilindro();
  c->setRotacion(40,40,0);
  menuFormas.agregarElemento(c,new ComandoCambiarFormaCilindro());
  c=new Cono();
  c->setRotacion(-90,0,0);
  menuFormas.agregarElemento(c,new ComandoCambiarFormaCono());
  menuVertexShader.cambiarOrientacion(MENU_VERTICAL);
  
  VertexShader vshaderEsferizar = cargarVshader("shaders/esferizar.vert");
  VertexShader vshaderSimple = cargarVshader("shaders/simple.vert");
  VertexShader vshaderIlumSimple = cargarVshader("shaders/simple_ilum.vert");
  VertexShader vshaderIlumTextura = cargarVshader("shaders/textura.vert");
  VertexShader vshaderOndas = cargarVshader("shaders/ondas.vert");
  VertexShader vshaderTorcido = cargarVshader("shaders/torcido.vert");
  VertexShader vshaderRotado = cargarVshader("shaders/rotar.vert");
  vshaderNormal = vshaderSimple;
  vshaderNormalIluminacion = vshaderIlumSimple;


  FragmentShader fshaderSimple = cargarFshader("shaders/simple.frag");
  FragmentShader fshaderTextura = cargarFshader("shaders/textura.frag");
  fshaderNormal = fshaderSimple;
  FragmentShader fshaderSemimate = cargarFshader("shaders/semimate.frag");
  
  VertexShader vshaderReflejo = cargarVshader("shaders/reflejar.vert");
  FragmentShader fshaderReflejo = cargarFshader("shaders/reflejar.frag");


  c=new Esfera();
  c->setColor(1,0,0);
  c->setVshaderForma(vshaderSimple); 
  c->setVshaderIluminacion(vshaderIlumSimple);
  c->setFshader(fshaderSimple);
  ComandoCompuesto *cc1 = new ComandoCompuesto;
  cc1->agregarComando(new ComandoCambiarColor(1,0,0));
  cc1->agregarComando(new ComandoCambiarVShaderIluminacion(vshaderIlumSimple));
  cc1->agregarComando(new ComandoCambiarFShader(fshaderSimple));
  menuFragmentShader.agregarElemento(c, cc1);
  
  c=new Esfera();
  ComandoCompuesto *cc2 = new ComandoCompuesto;
  cc2->agregarComando(new ComandoCambiarFShader(fshaderTextura));
  ComandoCambiarTextura* ladrillo = new ComandoCambiarTextura("lad.raw");
  cc2->agregarComando(ladrillo);
  c->setTextura(ladrillo->getTextura());
  c->setVshaderForma(vshaderSimple);
  c->setVshaderIluminacion(vshaderIlumSimple);
  c->setFshader(fshaderTextura);
  menuFragmentShader.agregarElemento(c, cc2);
  
  
  c = new Esfera();
  c->setColor(1, 1, 1);
  ComandoCambiarTexturaCubica* cubo = new ComandoCambiarTexturaCubica("cubemaps/cubemap_landscape/landscape");
  c->setTexturaCubica(cubo->getTextura());
  c->setVshaderForma(vshaderSimple);
  c->setVshaderIluminacion(vshaderReflejo);
  c->setFshader(fshaderReflejo);
  ComandoCompuesto * cubo_shaders = new ComandoCompuesto;
  cubo_shaders->agregarComando(cubo);
  cubo_shaders->agregarComando(new ComandoCambiarVShaderIluminacion(vshaderReflejo));
  cubo_shaders->agregarComando(new ComandoCambiarFShader(fshaderReflejo));
  menuFragmentShader.agregarElemento(c, cubo_shaders);

  c=new Esfera();
  c->setColor(0,1,0);
  c->setVshaderForma(vshaderSimple); 
  c->setVshaderIluminacion(vshaderIlumSimple);
  c->setFshader(fshaderSemimate);
  ComandoCompuesto *cc3 = new ComandoCompuesto;
  cc3->agregarComando(new ComandoCambiarColor(0,1,0));
  cc3->agregarComando(new ComandoCambiarVShaderIluminacion(vshaderIlumSimple));
  cc3->agregarComando(new ComandoCambiarFShader(fshaderSemimate));
  menuFragmentShader.agregarElemento(c, cc3);
  
  c=new Cubo();
  c->setVshaderForma(vshaderSimple);
  c->setVshaderIluminacion(vshaderIlumSimple);
  c->setFshader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarVShaderForma(vshaderSimple));

  c=new Cubo();
  c->setVshaderForma(vshaderEsferizar);
  c->setVshaderIluminacion(vshaderIlumSimple);
  c->setFshader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarVShaderForma(vshaderEsferizar));
  
  c=new Cubo();
  c->setVshaderIluminacion(vshaderIlumSimple);
  c->setVshaderForma(vshaderOndas);
  c->setFshader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarVShaderForma(vshaderOndas));
  
  c=new Cubo();
  c->setRotacion(-90,0,0);
  c->setVshaderForma(vshaderTorcido);
  c->setVshaderIluminacion(vshaderIlumSimple);
  c->setFshader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarVShaderForma(vshaderTorcido));
  
  c=new Cubo();
  c->setRotacion(90,0,0);
  c->setVshaderForma(vshaderRotado);
  c->setVshaderIluminacion(vshaderIlumSimple);
  c->setFshader(fshaderSimple);
  menuVertexShader.agregarElemento(c, new ComandoCambiarVShaderForma(vshaderRotado));
}


FragmentShader MundoTP2::cargarFshader(const char* archivo){
  FragmentShader fshader;
  if(!fshader.cargarDesdeArchivo(archivo)){
    std::cout << "FLOG:" << fshader.getInfoLog() << "\n";
    exit(0);
  }
  return fshader;
}

VertexShader MundoTP2::cargarVshader(const char* archivo){
 VertexShader vshader;
  if(!vshader.cargarDesdeArchivo(archivo)){
    std::cout << "VLOG:" << vshader.getInfoLog() << "\n";
    exit(0);
  }
  return vshader;
}


void MundoTP2::inicializar() {
    glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    GLfloat light[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, light);
    GLfloat light_position0[] = { 5.0, 5.0, 5.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0); 
    glEnable(GL_LIGHT0);

    
    GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_position[] = { - 5.0, -15.0, 5.0, 0.0 };
    GLfloat spot_direction[] = { 1.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
//    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
//    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
//    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
    glEnable(GL_LIGHT1);
    crearMenues();
    cambiarFigura(new Cubo);
}


void MundoTP2::vistaOrtogonal(){
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho(-(float)ancho_ventana/alto_ventana,(float)ancho_ventana/alto_ventana,-1,1,-30,30);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0,0,2,0,0,0,0,1,0);
  glGetFloatv(GL_MODELVIEW_MATRIX, matriz_camara);
  glLoadIdentity();

}

void MundoTP2::vistaPerspectiva(){
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (GLfloat)ancho_ventana/(GLfloat)alto_ventana, 0.10, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0,0,2,0,0,0,0,1,0);
  glGetFloatv(GL_MODELVIEW_MATRIX, matriz_camara);
  glLoadIdentity();

}

void MundoTP2::display(){
  glViewport (0, 0, (GLsizei) ancho_ventana, (GLsizei) alto_ventana);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  // Menues  
  if(mostrar_menu) { 
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
  }
  
  //Objeto central
  vistaPerspectiva();
  glColor3f(1,0,0);
  glTranslatef(0,-0.25,0);
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
			figura->rotarX(1);
		else if(x_mouse > x)
				figura->rotarX(-1);
		x_mouse = x;
		if (y_mouse < y)
			figura->rotarY(1);
		else
			if(y_mouse > y)
				figura->rotarY(-1);
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

void MundoTP2::cambiar_estado_luz_1() {
    if (luz_1_encendida) {
        glDisable(GL_LIGHT0);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat light_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        luz_1_encendida = false;
    }
    else {
        glEnable(GL_LIGHT0);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        luz_1_encendida = true;
    }
}

void MundoTP2::cambiar_estado_luz_2() {
    if (luz_2_encendida) {
        glDisable(GL_LIGHT1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 0.0);
        GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat light_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	luz_2_encendida = false;
    }
    else {
        glEnable(GL_LIGHT1);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
        luz_2_encendida = true;
    }
}

void MundoTP2::cambiar_estado_menu() {
    mostrar_menu = !mostrar_menu;
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
	    figura->rotarX(angulo);
	if(y)
	    figura->rotarY(angulo);
	if(z)
	    figura->rotarZ(angulo);
}

void MundoTP2::cambiarFigura(Cuerpo* cuerpo){
  if(figura != NULL){
	  desanimar(figura);
	  delete figura;
  }
  figura=cuerpo;
  figura->setVshaderForma(vshaderNormal);
  figura->setVshaderIluminacion(vshaderNormalIluminacion);
  figura->setFshader(fshaderNormal);
  rotarFigura(45,1,1,1);
}

void MundoTP2::resetearRotacion(){
 figura->setRotacion(0,0,0);
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

std::vector< bool > MundoTP2::obtenerEstadoLuces(){
  std::vector<bool> luces;
  luces.push_back(luz_1_encendida);
  luces.push_back(luz_2_encendida);
  return luces;
}

float* MundoTP2::getMatrizCamara(){
  return matriz_camara;
}

