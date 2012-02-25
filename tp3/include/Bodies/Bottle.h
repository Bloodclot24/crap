#ifndef _BOTTLE_H_
#define _BOTTLE_H_

#include "Body.h"
#include "Primitives/SuperficieRevolucion.h"
#include "Curves/Bezier.h"

class Bottle : public Body
{
    SuperficieRevolucion* superficie;
    float height_;
    float fillLevel;
    bool label;
    float labelTime;
    Bezier perfil_;

    void crearSuperficie();

public:
    Bottle(Bezier perfil);
    void draw();
    bool fill(float quantity);
    bool putLabel(float step);
    virtual ~Bottle();
};

#endif /* _BOTTLE_H_ */
