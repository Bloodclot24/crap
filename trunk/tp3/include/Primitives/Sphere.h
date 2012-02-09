#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <GL/glu.h>

#include "Primitive.h"

class Sphere : public Primitive
{
    private:
    float radius_;
    GLUquadric* quadric_;

    public:
    Sphere(float radius);
    void draw();
    ~Sphere();
};

#endif /* _SPHERE_H_ */
