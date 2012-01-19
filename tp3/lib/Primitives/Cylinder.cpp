#include "Primitives/Cylinder.h"

Cylinder::Cylinder(float radius, float height)
{
    radius_ = radius;
    height_ = height;
    quadric_ = gluNewQuadric();
}

void Cylinder::draw()
{
    gluCylinder(quadric_, radius_, radius_, height_, 15, 4);
}

Cylinder::~Cylinder()
{
    gluDeleteQuadric(quadric_);
}
