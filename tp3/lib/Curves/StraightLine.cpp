#include "Curves/StraightLine.h"

StraightLine::StraightLine(Vertex v0, Vertex v1)
{
    v0_ = v0;
    v1_ = v1;
    orientation_.setCoords(0, 0, 1);
}

Vertex StraightLine::getPoint(float t)
{
    Vertex point;

    point = v0_ + (v1_ - v0_)*t;

    return point;
}

Vertex StraightLine::getNormalAtPoint(float t)
{
    return orientation_.crossProduct(getTangentAtPoint(t)).normalize();
}

Vertex StraightLine::getTangentAtPoint(float t)
{
    return (v1_-v0_).normalize();
}

StraightLine::~StraightLine()
{

}
