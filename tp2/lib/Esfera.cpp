#include "Esfera.h"
#include <GL/glut.h>

void Esfera::do_dibujar(){
    glutSolidSphere(0.5, 20, 20);
}