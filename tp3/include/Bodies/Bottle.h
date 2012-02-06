#ifndef _BOTTLE_H_
#define _BOTTLE_H_

#include "Body.h"
#include "Primitives/Cylinder.h"
#include "Primitives/SuperficieRevolucion.h"

class Bottle : public Body
{
    Cylinder cylinder_;
    SuperficieRevolucion* superficie;

    void crearSuperficie();

public:
    Bottle();
    void draw();
    virtual ~Bottle();
};

#endif /* _BOTTLE_H_ */
