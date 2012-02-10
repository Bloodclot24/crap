#include "Curves/BSpline.h"

#include <math.h>

BSpline::BSpline(vectorPuntos controlPoints)
{
    degree_ = 2;
    controlPoints_ = controlPoints;
}

btVector3 BSpline::getPoint(float t)
{
    if(t>1)
        t=t-floor(t);

    unsigned segment = floor(controlPoints_.size()*t);

    float u = controlPoints_.size()*t - segment;

    float b0 = 0.5 * (1 - u) * (1 - u);
    float b1 = 0.5 * (1 + u) * (1 - u) + 0.5 * u * (2 - u);
    float b2 = 0.5 * u * u;
    return 
        b0 * controlPoints_[segment]   + 
        b1 * controlPoints_[segment+1] + 
        b2 * controlPoints_[segment+2];
}

btVector3 BSpline::getTangent(float t)
{

    if(t>1)
        t=t-floor(t);

    unsigned segment = floor(controlPoints_.size()*t);

    float u = controlPoints_.size()*t - segment;

    float tgb0 = u - 1;
    float tgb1 = 1 - 2 * u;
    float tgb2 = u;
    return 
        tgb0 * controlPoints_[segment]   + 
        tgb1 * controlPoints_[segment+1] + 
        tgb2 * controlPoints_[segment+2];
}
