#include "Menu.h"
#include <GL/gl.h>
#include <algorithm>
#include <iostream>
#include <GL/glut.h>

void Menu::agregarElemento(Cuerpo* icono, Command* accion){
  iconos.push_back(icono);
  comandos.push_back(accion);
  calcularPosiciones();
}

void Menu::calcularPosiciones(){
  int cantidad_elementos = iconos.size();
  posiciones.clear();
  espacio_total=MENU_ESPACIO_ENTRE_ELEMENTOS;
  otro_espacio=0;
  
  for(int i=0;i<cantidad_elementos;i++){
      float espacio;
      if(orientacion == MENU_HORIZONTAL){
	espacio = iconos[i]->getAncho();
	otro_espacio = std::max(iconos[i]->getAlto()*MENU_ESCALA_ELEMENTOS, otro_espacio);
      }
      else{
	espacio = iconos[i]->getAlto();
	otro_espacio = std::max(iconos[i]->getAncho()*MENU_ESCALA_ELEMENTOS, otro_espacio);
      }
      
      posiciones.push_back(espacio_total+espacio*MENU_ESCALA_ELEMENTOS/2);
      espacio_total += espacio*MENU_ESCALA_ELEMENTOS + MENU_ESPACIO_ENTRE_ELEMENTOS;
  }
  
  centro = espacio_total / 2;
  otro_espacio += MENU_ESPACIO_ENTRE_ELEMENTOS;
}

void Menu::dibujar(){
  glGetDoublev(GL_MODELVIEW_MATRIX, model);
  
  glGetDoublev(GL_PROJECTION_MATRIX, proj);
  
  glGetIntegerv(GL_VIEWPORT, viewport);

  int cantidad_elementos = iconos.size();
  glDisable(GL_LIGHTING);
  glLineWidth(7);
  
  float xCord, yCord;
  
  xCord=-centro+espacio_total; //x maximo
  yCord=otro_espacio/2; //y maximo
  
  if(orientacion != MENU_HORIZONTAL){
    float temp=xCord;
    xCord=yCord;
    yCord=temp;
  }
  
  std::cout << "total: " << espacio_total << " centro: " << centro << " otro: " << otro_espacio << "\n";
  glColor4f(72.0/255, 167.0/255, 255.0/255,0.5);
  glBegin(GL_QUADS);
  glVertex3f(-xCord, -yCord,0);
  glVertex3f(-xCord,  yCord,0);
  glVertex3f(xCord,   yCord,0);
  glVertex3f(xCord, -yCord,0);
  glEnd();
  
  glColor3f(0.0/255, 255.0/255, 192.0/255);
  glBegin(GL_LINE_LOOP);
  glVertex3f(-xCord, -yCord,0);
  glVertex3f(-xCord,  yCord,0);
  glVertex3f(xCord,   yCord,0);
  glVertex3f(xCord, -yCord,0);
  glEnd();
  glEnable(GL_LIGHTING);
  
  for(int i=0;i<cantidad_elementos;i++){
    glPushMatrix();
    if(orientacion == MENU_HORIZONTAL)
      glTranslatef(posiciones[i]-centro, 0, 0);
    else glTranslatef(0, posiciones[i]-centro, 0);
    
    glScalef(MENU_ESCALA_ELEMENTOS, MENU_ESCALA_ELEMENTOS, MENU_ESCALA_ELEMENTOS);
    iconos[i]->dibujar();
    glPopMatrix();
  }
}

Menu::Menu(MENU_ORIENTACION orientacion){
  this->orientacion = orientacion;
}

bool Menu::verificarRango(float posicion, float centro, float longitud){
    float max, min;
    min=centro-longitud/2;
    max=centro+longitud/2;
   
    return (posicion >= min && posicion <= max);
}

void Menu::click(int x, int y){
  int cantidad_elementos = iconos.size();
  std::cout << "Click: " << x << "  " << y << "\n";
  double xu,yu,zu;
  gluUnProject(x, y, 0, model, proj, viewport, &xu, &yu, &zu);
  yu=-yu;
  std::cout << "Clicku: " << xu << "  " << yu << " centro " << centro <<  "\n";
  for(int i=0;i<cantidad_elementos;i++){
    float posx, posy;
    
    if(orientacion == MENU_HORIZONTAL){
      posx=posiciones[i]-centro;
      posy=0;
    }
    else{
     posx=0;
     posy=posiciones[i]-centro;
    }
    
    std::cout << "posx " << posx << " posy " << posy << "\n";
    
    if(verificarRango(xu, posx, iconos[i]->getAncho()*MENU_ESCALA_ELEMENTOS))
      if(verificarRango(yu, posy, iconos[i]->getAlto()*MENU_ESCALA_ELEMENTOS)){
	//click en un elemento
	comandos[i]->ejecutar();
	glutPostRedisplay();
	return;
      }
  }
}

void Menu::cambiarOrientacion(MENU_ORIENTACION orientacion){
  this->orientacion = orientacion;
}

std::vector<Cuerpo*> Menu::getCuerpos() {
	return iconos;
}

std::vector<Command*> Menu::getComandos(){
	return comandos;
}
