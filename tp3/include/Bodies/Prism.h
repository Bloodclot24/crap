#ifndef _PRISM_H_
#define _PRISM_H_

#include "Vertex.h"
#include "Body.h"

#include <vector>

class Prism : public Body
{
    std::vector<Vertex> vertexes_;
    float height_;

    public:
    Prism(Vertex *vertexes, int n, float height);
    Prism();
    void draw();
    virtual ~Prism();
};

#endif /* _PRISM_H_ */
