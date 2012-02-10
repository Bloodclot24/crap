#include "Curves/StraightLine.h"

StraightLine::StraightLine(btVector3 v0, btVector3 v1)
{
    v0_ = v0;
    v1_ = v1;
    orientation_.setValue(0, 0, 1);
}

btVector3 StraightLine::getPoint(float t)
{
    btVector3 point;

    point = v0_ + (v1_ - v0_)*t;

    return point;
}

btVector3 StraightLine::getNormal(float t)
{
    return orientation_.cross(getTangent(t)).normalize();
}

btVector3 StraightLine::getTangent(float t)
{
    return (v1_-v0_).normalize();
}

StraightLine::~StraightLine()
{

}
