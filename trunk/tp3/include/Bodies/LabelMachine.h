#ifndef _LABELMACHINE_H_
#define _LABELMACHINE_H_

#include "Machine.h"
#include "Primitives/Cylinder.h"


class LabelMachine : public Machine
{
    Cylinder cylinder_;

public:
    LabelMachine();
    void draw();
    virtual ~LabelMachine();
};

#endif /* _LABELMACHINE_H_ */
