#include "Vertex.h"
#include <math.h>

Vertex::Vertex()
{
    x_ = y_ = z_ = 0;
}

void Vertex::setCoords(float x, float y,float z)
{
    setX(x);
    setY(y);
    setZ(z);
}

float Vertex::getX()
{
    return x_;
}

float Vertex::getY()
{
    return y_;
}

float Vertex::getZ()
{
    return z_;
}

void Vertex::setX(float x)
{
    x_ = x;
}

void Vertex::setY(float y)
{
    y_ = y;
}

void Vertex::setZ(float z)
{
    z_ = z;
}


Vertex Vertex::operator-(Vertex v)
{
    Vertex newVertex;
    
    newVertex.setCoords(getX()-v.getX(),
                        getY()-v.getY(),
                        getZ()-v.getZ());

    return newVertex;
}


Vertex Vertex::operator+(Vertex v)
{
    Vertex newVertex;
    
    newVertex.setCoords(getX()+v.getX(),
                        getY()+v.getY(),
                        getZ()+v.getZ());

    return newVertex;
}

Vertex Vertex::operator*(float t)
{
    Vertex newVertex;
    newVertex.setCoords(t*getX(),
                        t*getY(),
                        t*getZ());

    return newVertex;
}

float Vertex::abs()
{
    return sqrt(getX()*getX() + getY()*getY() + getZ()*getZ());
}

Vertex Vertex::normalize()
{
    float module = this->abs();

    Vertex newPoint;

    newPoint.setCoords(getX()/module,
                       getY()/module,
                       getZ()/module);
    return newPoint;
}
