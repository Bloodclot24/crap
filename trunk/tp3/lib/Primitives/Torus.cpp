#include "Primitives/Torus.h"

#include <GL/glut.h>

Torus::Torus(float innerRadius, float outerRadius)
{
	innerRadius_ = innerRadius;
	outerRadius_ = outerRadius;
}

void Torus::draw()
{
    glutSolidTorus(innerRadius_, outerRadius_, 15, 4);
}
