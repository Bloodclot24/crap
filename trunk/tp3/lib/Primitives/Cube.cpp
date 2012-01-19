#include "Primitives/Cube.h"

#include <GL/glut.h>

Cube::Cube(float size)
{
    size_ = size;
}

void Cube::draw()
{
    glutSolidCube(size_);
}
