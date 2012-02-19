#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "btBulletDynamicsCommon.h"//cambiar esto


typedef std::vector<btVector3> vectorPuntos; //cambiar de lugar
typedef std::vector<vectorPuntos> matrizPuntos;

class Primitive
{
    bool compiled;
    GLuint compiledList;
    static bool useCompiledLists_;

    virtual void drawPrimitive()=0;

    public:
    Primitive();
    void draw();

    static void useCompiledLists(bool state);
    
    virtual ~Primitive();
};

#endif /* _PRIMITIVE_H_ */
