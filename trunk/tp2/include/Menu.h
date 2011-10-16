#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "Cuerpo.h"
#include "Command.h"
#include <vector>

#define MENU_ESCALA_ELEMENTOS        0.3
#define MENU_ESPACIO_ENTRE_ELEMENTOS 0.2

class Menu{
private:
  std::vector<Command*> comandos;
  std::vector<Cuerpo*> iconos;

  
public:
  Menu();
  void agregarElemento(Cuerpo *icono, Command* accion);
  void dibujar();
  void click(int x, int y);
};

#endif
