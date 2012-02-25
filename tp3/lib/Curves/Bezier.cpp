#include "Curves/Bezier.h"

#include <math.h>

Bezier::Bezier()
{
    degree_ = 3;
}

Bezier::Bezier(vectorPuntos controlPoints)
{
    degree_ = 3;
    controlPoints_ = controlPoints;
}

btVector3 Bezier::getPoint(float t)
{
    if(t>1)
        t=1;

    if(controlPoints_.size() < degree_+1)
        return btVector3(0,0,0);

    int segments = (controlPoints_.size()-(degree_+1))/degree_ + 1;

    int offset = floor(t * segments);
    float u = (t * segments) - offset;


    btVector3 punto(0,0,0);

    if(offset == segments){
        punto = controlPoints_[offset*(degree_+1)];
    }
    else{
        for (unsigned i = 0; i < degree_ + 1; i++) {
            float c = factorial(degree_) /(factorial(i) * factorial(degree_ - i)) * pow(u,i) * pow(1-u,degree_-i);
            punto += c * controlPoints_[i+offset*degree_];
        }
    }
    
    return punto;
}

btVector3 Bezier::getTangent(float t)
{
    return btVector3(0,0,0);
}

btVector3 Bezier::getNormal(float t)
{
    return btVector3(0,0,0);
}


int Bezier::factorial(int n) {
    int resultado = 1;
    for (int i = 2; i <= n; i++)
        resultado = resultado * i;
    return resultado;
}
