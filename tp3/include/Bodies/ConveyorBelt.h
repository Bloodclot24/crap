#ifndef _CONVEYORBELT_H_
#define _CONVEYORBELT_H_

#include "Curve.h"
#include "Body.h"
#include "Bodies/Prism.h"

#include <vector>

class ConveyorBelt: public Body
{
    std::vector<Prism> prism_;
    int prisms_;

    void computePoints();
    void drawPatch(int i);

    public:
    ConveyorBelt(Curve *path);
    void draw();
    ~ConveyorBelt();
};

#endif /* _CONVEYORBELT_H_ */
