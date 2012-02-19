#ifndef _CUBE_H_
#define _CUBE_H_

#include "Primitive.h"

class Cube : public Primitive
{
    private:
    float size_;
    void drawPrimitive();

    public:
    Cube(float size);
};

#endif /* _CUBE_H_ */
