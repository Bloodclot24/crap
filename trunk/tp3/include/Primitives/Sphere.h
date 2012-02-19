#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Primitive.h"

#include <GL/glu.h>


class Sphere : public Primitive
{
    private:
    float radius_;
    GLUquadric* quadric_;

    void drawPrimitive();

    public:
    Sphere(float radius);
    ~Sphere();
};

#endif /* _SPHERE_H_ */
