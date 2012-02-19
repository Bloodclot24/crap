#include "Primitives/Torus.h"

#include <GL/glut.h>

Torus::Torus(float innerRadius, float outerRadius)
{
	innerRadius_ = innerRadius;
	outerRadius_ = outerRadius;
}

void Torus::drawPrimitive()
{
    glutSolidTorus(innerRadius_, outerRadius_, 15, 4);
}
