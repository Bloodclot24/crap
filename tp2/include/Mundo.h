#ifndef MUNDO_H_INCLUDED
#define MUNDO_H_INCLUDED

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "ManejadorTecla.h"
#include <map>

class Mundo {
protected:
  static Mundo* te_odio;
  int ancho_ventana, alto_ventana;
  Mundo();
private:
    
    std::string nombreMundo;
    std::map<char, ManejadorTecla*> teclas;
    
    virtual void inicializar();
    virtual void display();
    virtual void reshape(int x, int y);
    virtual void keyboard(unsigned char key, int x, int y);
    virtual void mouse(int button, int state, int x, int y);
    virtual void motion(int x, int y);
    
    static void display_static();
    static void reshape_static(int w, int h);
    static void keyboard_static(unsigned char key, int x, int y);
    static void mouse_static(int button, int state, int x, int y);
    static void pmotion_static(int x, int y);
    Mundo(const Mundo&);
public:
    
    static Mundo* get_instance();
    void crearVentana(int w=1024, int h=768, int flags=GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    void comenzar();
    void agregarTecla(char tecla, ManejadorTecla *manejador);
};

#endif
