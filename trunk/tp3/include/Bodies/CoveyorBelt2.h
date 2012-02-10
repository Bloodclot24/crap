#ifndef _COVEYORBELT_H_
#define _COVEYORBELT_H_

#include "Primitives/SuperficieBarrido.h"
#include "Body.h"
#include "Curves/BSpline.h"

class CoveyorBelt : public Body
{
    SuperficieBarrido* superficie;

    float displacement;

    void crearSuperficie();

    BSpline bspline_;
    
    public:
    
    CoveyorBelt();
    void draw();

    btVector3 getPosition(float t);
    btVector3 getTangent(float t);

    void advance(float amount);

    virtual ~CoveyorBelt();
};

#endif /* _COVEYORBELT_H_ */
