#include "Primitives/Sphere.h"

#include <GL/glut.h>

Sphere::Sphere(float radius)
{
	radius_ = radius;
    quadric_ = gluNewQuadric();
}

void Sphere::drawPrimitive()
{
	gluSphere(quadric_, radius_, 30, 20);
	//glutSolidSphere(radius_,15,4);
}

Sphere::~Sphere()
{
    gluDeleteQuadric(quadric_);
}
