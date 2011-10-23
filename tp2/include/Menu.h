#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "Cuerpo.h"
#include "Command.h"
#include <vector>

enum MENU_ORIENTACION { MENU_HORIZONTAL, MENU_VERTICAL};
#define MENU_ESCALA_ELEMENTOS        0.3
#define MENU_ESPACIO_ENTRE_ELEMENTOS 0.1

class Menu{
private:
  std::vector<Command*> comandos;
  std::vector<Cuerpo*> iconos;
  std::vector<float> posiciones;
  MENU_ORIENTACION orientacion;
  float espacio_total;
  double otro_espacio;
  float centro;
  double model[16];
  double proj[16];
  int viewport[4];

  void calcularPosiciones();
  bool verificarRango(float posicion, float centro, float longitud);
  
public:
  Menu(MENU_ORIENTACION orientacion=MENU_HORIZONTAL);
  void agregarElemento(Cuerpo *icono, Command* accion);
  void dibujar();
  void click(int x, int y);
  void cambiarOrientacion(MENU_ORIENTACION orientacion);
  std::vector<Cuerpo*> getCuerpos();
  std::vector<Command*> getComandos();
};

#endif
