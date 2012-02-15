#ifndef _LABELMACHINE_H_
#define _LABELMACHINE_H_

#include "Machine.h"
#include "Primitives/Cylinder.h"


class LabelMachine : public Machine
{
    Cylinder cylinder_;
    float level;
    bool subiendo;

public:
    LabelMachine();
    void draw();
    bool process(Bottle* bottle, float step);
    virtual ~LabelMachine();
};

#endif /* _LABELMACHINE_H_ */
