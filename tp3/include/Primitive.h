#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "btBulletDynamicsCommon.h"//cambiar esto

typedef std::vector<btVector3> vectorPuntos; //cambiar de lugar
typedef std::vector<vectorPuntos> matrizPuntos;

class Primitive
{
    public:
    Primitive();
    virtual void draw()=0;
    virtual ~Primitive();
};

#endif /* _PRIMITIVE_H_ */
