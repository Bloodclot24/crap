#ifndef _CILYNDER_H_
#define _CILYNDER_H_

#include "Primitive.h"

#include <GL/glu.h>


class Cylinder : public Primitive
{
    float radius_, height_;

    GLUquadric* quadric_;
    GLUquadric* topDiskQuadric_;
    GLUquadric* downDiskQuadric_;
    void drawPrimitive();

    public:
    Cylinder(float radius, float height);
    ~Cylinder();
};

#endif /* _CILYNDER_H_ */
