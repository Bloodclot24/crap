#ifndef _CURVE_H_
#define _CURVE_H_

#include "btBulletDynamicsCommon.h"



class Curve
{
    public:
    class Iterator
    {
        private:
        int currentStep_;
        int totalSteps_;
        Curve* curve_;

        public:
        btVector3 next();
        btVector3 normal();
        bool hasNext();

        protected:
        Iterator(Curve* curve, int totalSteps);

        friend class Curve;
    };

    Curve();
    virtual btVector3 getPoint(float t)=0;
    virtual btVector3 getNormal(float t)=0;
    virtual btVector3 getTangent(float t)=0;
    virtual Curve::Iterator iterator(int steps);
    virtual ~Curve();
};

#endif /* _CURVE_H_ */
