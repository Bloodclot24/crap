#ifndef _CURVE_H_
#define _CURVE_H_

#include "Vertex.h"

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
        Vertex next();
        Vertex normal();
        bool hasNext();

        protected:
        Iterator(Curve* curve, int totalSteps);

        friend class Curve;
    };

    Curve();
    virtual Vertex getPoint(float t)=0;
    virtual Vertex getNormalAtPoint(float t)=0;
    virtual Vertex getTangentAtPoint(float t)=0;
    virtual Curve::Iterator iterator(int steps);
    virtual ~Curve();
};

#endif /* _CURVE_H_ */
