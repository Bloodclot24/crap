#include "GlVertex.h"

#include <GL/gl.h>


void glVertex(Vertex v)
{
    glVertex3f(v.getX(), v.getY(), v.getZ());
}


void glNormal(Vertex v)
{
    glNormal3f(v.getX(), v.getY(), v.getZ());
}
