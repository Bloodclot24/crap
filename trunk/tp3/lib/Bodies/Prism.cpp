#include "Bodies/Prism.h"
#include <string.h>
#include <GL/gl.h>
#include "GLTexture.h"

Prism::Prism()
{
    height_ = 0;
}

Prism::Prism(vectorPuntos vertexes, float height)
{
    vertexes_ = vertexes;
    height_ = height;
}

Prism::Prism(btVector3 *vertexes, int n, float height)
{
    for(int i = 0; i<n; i++)
        vertexes_.push_back(vertexes[i]);
    height_ = height;
}

void Prism::draw()
{
    glColor3f(1, 1, 1);
    GLTexture::bind("chapa");

    float displacementMagnitude  = height_/2;
    btVector3 displacementDirection = (vertexes_[1]-vertexes_[0]).cross(vertexes_[2]-vertexes_[1]);

    btVector3 displacement = displacementDirection.normalize() * displacementMagnitude;

    int n = vertexes_.size();

    float textureVertex[4][2] = {{1,0},{0,0},{0,1},{1,1}};
    glBegin(GL_POLYGON);{
        glNormal3fv(displacementDirection);
        for(int i=0;i<n;i++) {
        	glTexCoord2fv(textureVertex[i]);
            glVertex3fv(vertexes_[i]+displacement);
        }
    }glEnd();

    vectorPuntos vertexesPlus = vertexes_;
    vertexesPlus.push_back(vertexes_[0]);

    glBegin(GL_QUADS);{
        for(int i=0;i<n;i++)
        {
            glNormal3fv( (vertexesPlus[i+1]-vertexesPlus[i]).cross(displacement));

            glTexCoord2fv(textureVertex[0]);
            glVertex3fv(vertexesPlus[i]+displacement);
            glTexCoord2fv(textureVertex[3]);
            glVertex3fv(vertexesPlus[i]-displacement);
            glTexCoord2fv(textureVertex[2]);
            glVertex3fv(vertexesPlus[i+1]-displacement);
            glTexCoord2fv(textureVertex[1]);
            glVertex3fv(vertexesPlus[i+1]+displacement);
        }
    }glEnd();

    glBegin(GL_POLYGON);{
        glNormal3fv(-displacement);
        for(int i=0;i<n;i++){
        	glTexCoord2fv(textureVertex[i]);
            glVertex3fv(vertexes_[i]-displacement);
        }
    }glEnd();
}

Prism::~Prism()
{
}
