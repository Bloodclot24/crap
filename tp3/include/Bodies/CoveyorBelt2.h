#ifndef _COVEYORBELT_H_
#define _COVEYORBELT_H_

#include "Primitives/SuperficieBarrido.h"
#include "Body.h"

class CoveyorBelt : public Body
{
    SuperficieBarrido* superficie;

    float displacement;

    void crearSuperficie();
    
    public:
    
    CoveyorBelt();
    void draw();

    btVector3 getPosition(float t);

    void advance(float amount);

    virtual ~CoveyorBelt();
};

#endif /* _COVEYORBELT_H_ */
