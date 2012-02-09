#include "Primitives/Cylinder.h"

Cylinder::Cylinder(float radius, float height)
{
    radius_ = radius;
    height_ = height;
    quadric_ = gluNewQuadric();
    topDiskQuadric_ = gluNewQuadric();
    downDiskQuadric_ = gluNewQuadric();
}

void Cylinder::draw()
{
    gluCylinder(quadric_, radius_, radius_, height_, 15, 4);

	glPushMatrix();{
    	glTranslatef(0,0,height_);
    	gluDisk(topDiskQuadric_, 0, radius_, 15, 4);
    	glTranslatef(0,0,-height_);
    	gluDisk(downDiskQuadric_, 0.9*radius_, radius_, 15, 4);
    }glPopMatrix();
}

Cylinder::~Cylinder()
{
    gluDeleteQuadric(quadric_);
    gluDeleteQuadric(topDiskQuadric_);
    gluDeleteQuadric(downDiskQuadric_);
}
