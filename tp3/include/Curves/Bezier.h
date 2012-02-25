#ifndef _BEZIER_H_
#define _BEZIER_H_

#include "Curve.h"
#include "Primitive.h"

class Bezier: public Curve
{

    unsigned degree_;
    vectorPuntos controlPoints_;
    public:
    Bezier(vectorPuntos controlPoints);
    Bezier();
    btVector3 getPoint(float t);
    btVector3 getTangent(float t);
    btVector3 getNormal(float t);

    int factorial(int n);

};

#endif /* _BEZIER_H_ */
