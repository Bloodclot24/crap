#ifndef _BOTTLE_H_
#define _BOTTLE_H_

#include "Body.h"
#include "Primitives/SuperficieRevolucion.h"

#define BOTTLE_SCALE 1

class Bottle : public Body
{
    SuperficieRevolucion* superficie;
    float height_;

    void crearSuperficie();

public:
    Bottle();
    void draw();
    virtual ~Bottle();
};

#endif /* _BOTTLE_H_ */
