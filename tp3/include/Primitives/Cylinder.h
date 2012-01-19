#ifndef _CILYNDER_H_
#define _CILYNDER_H_

#include <GL/glu.h>

#include "Primitive.h"

class Cylinder : public Primitive
{

    float radius_, height_;

    GLUquadric* quadric_;

    public:
    Cylinder(float radius, float height);
    void draw();
    ~Cylinder();
};

#endif /* _CILYNDER_H_ */
