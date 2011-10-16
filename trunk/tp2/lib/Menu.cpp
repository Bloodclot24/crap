#include "Menu.h"
#include "GL/gl.h"

void Menu::agregarElemento(Cuerpo* icono, Command* accion){
  iconos.push_back(icono);
  comandos.push_back(accion);
}

void Menu::dibujar(){
  int cantidad_elementos = iconos.size();
  
  std::vector<float> posiciones;

  float ancho_total=MENU_ESPACIO_ENTRE_ELEMENTOS;
  for(int i=0;i<cantidad_elementos;i++){
      posiciones.push_back(ancho_total+iconos[i]->getAncho()*MENU_ESCALA_ELEMENTOS/2);
      ancho_total += iconos[i]->getAncho()*MENU_ESCALA_ELEMENTOS + MENU_ESPACIO_ENTRE_ELEMENTOS;
  }
  
  float centro = ancho_total / 2;
  
  for(int i=0;i<cantidad_elementos;i++){
    glPushMatrix();
    glTranslatef(posiciones[i]-centro, 0, 0);
    glScalef(MENU_ESCALA_ELEMENTOS, MENU_ESCALA_ELEMENTOS, MENU_ESCALA_ELEMENTOS);
    iconos[i]->dibujar();
    glPopMatrix();
  }
}

Menu::Menu(){

}

void Menu::click(int x, int y){

}
