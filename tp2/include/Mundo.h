#ifndef MUNDO_H_INCLUDED
#define MUNDO_H_INCLUDED

#include <GL/glut.h>
#include <iostream>
#include "ManejadorTecla.h"
#include <map>

class Mundo {
private:
    static Mundo* te_odio;
    std::string nombreMundo;
    float eye[3];
    float at[3];
    float up[3];
    float light_color[4];
    float light_position[3];
    float light_ambient[4];
    GLfloat window_size[2];
    GLuint dl_handle;
    bool view_axis;
    bool view_grid;
    bool edit_panel;
    
    std::map<char, ManejadorTecla*> teclas;
    
    void inicializar();
    void dibujarEjes();
    void dibujarEjesVista2D();
    void dibujarGrilla();
    void entorno3D();
    void entornoPanel();
    void display();
    void reshape(int x, int y);
    void keyboard(unsigned char key, int x, int y);
    
    static void display_static();
    static void reshape_static(int w, int h);
    static void keyboard_static(unsigned char key, int x, int y);
    static void pmotion_static(int x, int y);
public:
    Mundo(int argc, char** argv);
    void crearVentana(int w=1024, int h=768, int flags=GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    void comenzar();
    
    void cambiarVisibilidadPanel();
    void agregarTecla(char tecla, ManejadorTecla *manejador);
};

#endif