#ifndef _STRAIGHTLINE_H_
#define _STRAIGHTLINE_H_

#include "Curve.h"

class StraightLine:public Curve
{

    private:
    btVector3 v0_, v1_;
    btVector3 orientation_;

    public:
    StraightLine(btVector3 v0, btVector3 v1);

    virtual btVector3 getPoint(float t);
    virtual btVector3 getNormal(float t);
    virtual btVector3 getTangent(float t);
    virtual ~StraightLine();
};

#endif /* _STRAIGHTLINE_H_ */
