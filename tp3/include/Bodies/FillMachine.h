#ifndef _FILLMACHINE_H_
#define _FILLMACHINE_H_

#include "Machine.h"

#include "Primitives/Cylinder.h"
#include "Primitives/Sphere.h"
#include "Primitives/SuperficieBarrido.h"

class FillMachine : public Machine
{
    Cylinder cylinder_;
    SuperficieBarrido* manguera;
    Sphere sphere_;
    float level;
    bool subiendo;

    void crearManguera();

public:
    FillMachine();
    void draw();
    bool process(Bottle* bottle, float step);
    virtual ~FillMachine();
};

#endif /* _FILLMACHINE_H_ */
