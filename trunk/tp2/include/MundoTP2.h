#ifndef MUNDOTP2_H_INCLUDED
#define MUNDOTP2_H_INCLUDED


#include <vector>

#include "Mundo.h"
#include "Cuerpo.h"
#include "Menu.h"

class MundoTP2: public Mundo{
private:
  Cuerpo *figura;
  float rotX, rotY, rotZ;
  static MundoTP2 *te_odio2;
  Menu menuFragmentShader;
  Menu menuFormas;
  Menu menuVertexShader;


  MundoTP2();
  void display();
  void inicializar();
  void crearMenues();
  void vistaPerspectiva();
  void vistaOrtogonal();
  virtual void mouse(int button, int state, int x, int y);
  void destruirMenu(Menu menu);

public:
  static MundoTP2* get_instance();
  void rotarFigura(float angulo, bool x, bool y, bool z);
  void resetearRotacion();
  void cambiarFigura(Cuerpo *cuerpo);
  Cuerpo* obtenerCuerpo();
  static void destruir();
  ~MundoTP2();
};

#endif
