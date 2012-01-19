#ifndef _BOTTLE_H_
#define _BOTTLE_H_

#include "Body.h"
#include "Primitives/Cylinder.h"

class Bottle : public Body
{
    Cylinder cylinder_;

    public:
    Bottle();
    void draw();
    virtual ~Bottle();
};

#endif /* _BOTTLE_H_ */
