#ifndef _CUBE_H_
#define _CUBE_H_

#include "Primitive.h"

class Cube : public Primitive
{
    private:
    float size_;

    public:
    Cube(float size);
    void draw();
};

#endif /* _CUBE_H_ */
