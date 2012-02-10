#ifndef _PRISM_H_
#define _PRISM_H_

#include "Body.h"
#include "Primitive.h"

#include <vector>

class Prism : public Body
{
    vectorPuntos vertexes_;
    float height_;

    public:
    Prism(vectorPuntos vertexes, float height);
    Prism(btVector3 *vertexes, int n, float height);
    Prism();
    void draw();
    virtual ~Prism();
};

#endif /* _PRISM_H_ */
