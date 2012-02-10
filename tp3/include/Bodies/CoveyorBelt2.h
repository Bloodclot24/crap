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
    virtual ~CoveyorBelt();
};

#endif /* _COVEYORBELT_H_ */
