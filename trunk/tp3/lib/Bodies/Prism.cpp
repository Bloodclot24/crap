#include "Bodies/Prism.h"
#include <string.h>
#include <GL/gl.h>
#include "GlVertex.h"
#include "GLTexture.h"

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
    glColor3f(1, 1, 1);
    GLTexture::bind("chapa");

    float displacementMagnitude  = height_/2;
    Vertex displacementDirection = (vertexes_[1]-vertexes_[0]).crossProduct(vertexes_[2]-vertexes_[1]);

    Vertex displacement = displacementDirection.normalize() * displacementMagnitude;

    int n = vertexes_.size();

    float textureVertex[4][2] = {{1,0},{0,0},{0,1},{1,1}};
    glBegin(GL_POLYGON);{
        glNormal(displacementDirection);
        for(int i=0;i<n;i++) {
        	glTexCoord2fv(textureVertex[i]);
            glVertex(vertexes_[i]+displacement);
        }
    }glEnd();

    glBegin(GL_QUADS);{
        for(int i=0;i<n-1;i++)
        {
            glNormal( (vertexes_[i+1]-vertexes_[i]).crossProduct(displacement));

            glTexCoord2fv(textureVertex[0]);
            glVertex(vertexes_[i]+displacement);
            glTexCoord2fv(textureVertex[1]);
            glVertex(vertexes_[i+1]+displacement);
            glTexCoord2fv(textureVertex[2]);
            glVertex(vertexes_[i+1]-displacement);
            glTexCoord2fv(textureVertex[3]);
            glVertex(vertexes_[i]-displacement);
        }

        glNormal((vertexes_[0]-vertexes_[n-1]).crossProduct(displacement));
        glTexCoord2fv(textureVertex[0]);
        glVertex(vertexes_[n-1]+displacement);
        glTexCoord2fv(textureVertex[1]);
        glVertex(vertexes_[0]+displacement);
        glTexCoord2fv(textureVertex[2]);
        glVertex(vertexes_[0]-displacement);
        glTexCoord2fv(textureVertex[3]);
        glVertex(vertexes_[n-1]-displacement);
    }glEnd();

    glBegin(GL_POLYGON);{
        glNormal(-displacement);
        for(int i=0;i<n;i++){
        	glTexCoord2fv(textureVertex[i]);
            glVertex(vertexes_[i]-displacement);
        }
    }glEnd();
}

Prism::~Prism()
{
}
