#include "Bodies/ConveyorBelt.h"

#include "btBulletDynamicsCommon.h"

#include "GL/gl.h"
#include <stdio.h>
#include "GlVertex.h"

ConveyorBelt::ConveyorBelt(Curve *path)
{
    prisms_ = 10;

    Vertex point[prisms_];
    Vertex normal[prisms_];

    int i=0;

    for(Curve::Iterator it = path->iterator(prisms_+1);
        it.hasNext(); 
        i++)
    {
        point[i] = it.next();
        normal[i] = it.normal();
    }

    float displacement = 1;
    float height = 0.1;

    for(int i=0; i<prisms_; i++)
    {
        Vertex patch[4];

        patch[0] = point[i]   + normal[i]   * displacement;
        patch[1] = point[i+1] + normal[i+1] * displacement;
        patch[2] = point[i+1] - normal[i+1] * displacement;
        patch[3] = point[i]   - normal[i]   * displacement;

        Prism newPrism(patch, 4, height);
        prism_.push_back(newPrism);
    }
}

void ConveyorBelt::draw()
{
    glColor3f(0.2, 0.2, 0.2);

    for(int i=0; i<prisms_; i++)
        prism_[i].draw();
}

ConveyorBelt::~ConveyorBelt()
{
}
