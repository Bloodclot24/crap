#include "Curve.h"

Curve::Curve()
{

}

Curve::Iterator Curve::iterator(int steps)
{
    Curve::Iterator it(this, steps);
    return it;
}


Curve::Iterator::Iterator(Curve* curve, int totalSteps)
{
    curve_ = curve;
    currentStep_ = 0;
    totalSteps_ = totalSteps;
}

Vertex Curve::Iterator::next()
{
    Vertex vertex = curve_->getPoint(float(currentStep_)/float(totalSteps_));
    ++currentStep_;
    return vertex;
}

bool Curve::Iterator::hasNext()
{
    return currentStep_ <= totalSteps_;
}

Curve::~Curve()
{

}
