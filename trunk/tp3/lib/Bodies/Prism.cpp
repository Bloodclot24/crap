#include <string.h>

#include <GL/gl.h>

#include "Bodies/Prism.h"
#include "GlVertex.h"

Prism::Prism()
{
    height_ = 0;
}

Prism::Prism(Vertex *vertexes, int n, float height)
{
    for(int i=0; i < n; i++)
        vertexes_.push_back(vertexes[i]);

    height_ = height;
}

void Prism::draw()
{
    float displacementMagnitude  = height_/2;
    Vertex displacementDirection = (vertexes_[1]-vertexes_[0]).crossProduct(vertexes_[2]-vertexes_[1]);

    Vertex displacement = displacementDirection * displacementMagnitude;

    int n = vertexes_.size();

    glBegin(GL_POLYGON);{
        glNormal(displacementDirection);
        for(int i=0;i<n;i++)
            glVertex(vertexes_[i]+displacement);
    }glEnd();

    glBegin(GL_QUADS);{
        for(int i=0;i<n-1;i++)
        {
            glNormal(vertexes_[i] - vertexes_[i+1]);
            glVertex(vertexes_[i]+displacement);
            glVertex(vertexes_[i+1]+displacement);
            glVertex(vertexes_[i+1]-displacement);
            glVertex(vertexes_[i]-displacement);
        }

        glNormal(vertexes_[n-1]-vertexes_[0]);
        glVertex(vertexes_[n-1]+displacement);
        glVertex(vertexes_[0]+displacement);
        glVertex(vertexes_[0]-displacement);
        glVertex(vertexes_[n-1]-displacement);
    }glEnd();

    glBegin(GL_POLYGON);{
        glNormal(-displacement);
        for(int i=0;i<n;i++)
            glVertex(vertexes_[i]-displacement);
    }glEnd();
}

Prism::~Prism()
{
}