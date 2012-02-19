#include "Primitive.h"

#include <stdio.h>

bool Primitive::useCompiledLists_ = false;

Primitive::Primitive()
{
    compiled=false;
}

void Primitive::useCompiledLists(bool state)
{
    useCompiledLists_ = state;
    printf("Using compiled lists: %d\n", state);
}

void Primitive::draw()
{
    if(useCompiledLists_){
        if(!compiled){
            compiled=true;
            compiledList = glGenLists(1);
            glNewList(compiledList,GL_COMPILE);
            drawPrimitive();
            glEndList();
        }
        glCallList(compiledList);
    }
    else drawPrimitive();
}

Primitive::~Primitive()
{
    if(compiled)
        glDeleteLists(compiledList, 1);
}
