#include "Bodies/ConveyorBelt.h"

#include "btBulletDynamicsCommon.h"

#include "GL/gl.h"
#include <stdio.h>

ConveyorBelt::ConveyorBelt(Curve *path)
{
    prisms_ = 10;

    btVector3 point[prisms_];
    btVector3 normal[prisms_];

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
        vectorPuntos patches;

        patches[0] = point[i]   + normal[i]   * displacement;
        patches[1] = point[i+1] + normal[i+1] * displacement;
        patches[2] = point[i+1] - normal[i+1] * displacement;
        patches[3] = point[i]   - normal[i]   * displacement;

        Prism newPrism(patches, height);
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
