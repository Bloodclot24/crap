#ifndef _BOTTLE_H_
#define _BOTTLE_H_

#include "Body.h"
#include "Primitives/SuperficieRevolucion.h"

#define BOTTLE_SCALE 1

class Bottle : public Body
{
    SuperficieRevolucion* superficie;
    float height_;
    float fillLevel;

    void crearSuperficie();

public:
    Bottle();
    void draw();
    void fill(float quantity);
    virtual ~Bottle();
};

#endif /* _BOTTLE_H_ */
