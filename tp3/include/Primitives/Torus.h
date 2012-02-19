#ifndef _TORUS_H_
#define _TORUS_H_

#include "Primitive.h"

class Torus : public Primitive
{
    private:
    float innerRadius_;
    float outerRadius_;
    void drawPrimitive();


    public:
    Torus(float innerRadius_, float outerRadius_);
};

#endif /* _TORUS_H_ */
