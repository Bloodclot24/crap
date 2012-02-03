#ifndef _STRAIGHTLINE_H_
#define _STRAIGHTLINE_H_

#include "Curve.h"

class StraightLine:public Curve
{

    private:
    Vertex v0_, v1_;

    public:
    StraightLine(Vertex v0, Vertex v1);

    virtual Vertex getPoint(float t);
    virtual Vertex getNormalAtPoint(float t);
    virtual Vertex getTangentAtPoint(float t);
    virtual ~StraightLine();
};

#endif /* _STRAIGHTLINE_H_ */
