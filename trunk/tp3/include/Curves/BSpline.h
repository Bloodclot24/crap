#ifndef _BSPLINE_H_
#define _BSPLINE_H_

#include "Curve.h"
#include "Primitive.h"

class BSpline: public Curve
{
    unsigned degree_;
    vectorPuntos controlPoints_;
    public:
    BSpline(vectorPuntos controlPoints);
    BSpline();
    btVector3 getPoint(float t);
    btVector3 getTangent(float t);
    btVector3 getNormal(float t);

};

#endif /* _BSPLINE_H_ */
