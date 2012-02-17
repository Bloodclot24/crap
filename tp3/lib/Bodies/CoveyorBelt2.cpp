#include "Bodies/CoveyorBelt2.h"
#include "GLShader.h"
#include "GLTexture.h"

#include "btBulletDynamicsCommon.h"
#include <GL/glut.h>
#include <math.h>

CoveyorBelt::CoveyorBelt()
{
    crearSuperficie();
    displacement = 0;
}

void CoveyorBelt::draw()
{

    glColor3f(1, 1, 1);
    GLTexture::bind("cinta");

    GLShader::pushProgram("belt");

    GLShader::setUniform("displacement", displacement);

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(0,0,1);
    glBegin(GL_TRIANGLE_STRIP);
    float pasosi = superficie->getVertices().size() - 1;
    float pasosj = superficie->getVertices()[0].size() - 1;
    for (int i = 0; i < pasosi ; i++) {
        for (int j = 0; j <= pasosj; j++) {

            glNormal3fv(superficie->getNormales()[i][j]);
            glTexCoord2f( j /pasosj, i/pasosi*20);
            glVertex3fv(superficie->getVertices()[i][j]);

            glNormal3fv(superficie->getNormales()[i + 1][j]);
            glTexCoord2f( j /pasosj, (i+1)/pasosi*20);
            glVertex3fv(superficie->getVertices()[i + 1][j]);
        }
    }
    glEnd();
    glPopMatrix();

    GLShader::popProgram();
}

void CoveyorBelt::advance(float amount)
{
    displacement += amount;
}

btVector3 CoveyorBelt::getPosition(float t)
{
    if(t>1)
        t=1;
    return (bspline_.getPoint(t)+btVector3(0,0,1.1))*0.5;
}

btVector3 CoveyorBelt::getTangent(float t)
{
    if(t>1)
        t=1;
    return bspline_.getTangent(t)*0.5;
}

CoveyorBelt::~CoveyorBelt()
{
    delete superficie;
}

void CoveyorBelt::crearSuperficie() {
    std::vector<btVector3> perfil, normales, ptosControl;
   	perfil.push_back(btVector3(0,0.25,0));
    perfil.push_back(btVector3(0,-0.25,0));
    perfil.push_back(btVector3(0,-0.35,0.2));
    perfil.push_back(btVector3(0,-0.3,0.2));
    perfil.push_back(btVector3(0,-0.25,0.1));
    perfil.push_back(btVector3(0,0.25,0.1));
    perfil.push_back(btVector3(0,0.3,0.2));
    perfil.push_back(btVector3(0,0.35,0.2));
    perfil.push_back(btVector3(0,0.25,0));

    normales.push_back(btVector3(0, 1, -2));
    normales.push_back(btVector3(0, -1, -2));
    normales.push_back(btVector3(0, -2, 1));
    normales.push_back(btVector3(0, 1, 2));
    normales.push_back(btVector3(0, 1, 2));
    normales.push_back(btVector3(0, -1, 2));
    normales.push_back(btVector3(0, -1, 2));
    normales.push_back(btVector3(0, 2, 1));
    normales.push_back(btVector3(0, 1, -2));

    ptosControl.push_back(btVector3(-11.75, -1.25, 0));
    ptosControl.push_back(btVector3(-10.25, -3.75, 0));
    ptosControl.push_back(btVector3(-5.75, -4.25, 0));
    ptosControl.push_back(btVector3(-3.75, -2.25, 0));
    ptosControl.push_back(btVector3(-4.25, 2.25, 0));
    ptosControl.push_back(btVector3(-2.25, 4.25, 0));
    ptosControl.push_back(btVector3(2.25, 3.75, 0));
    ptosControl.push_back(btVector3(4.75, 4.25, 0));
    ptosControl.push_back(btVector3(7.75, 7.75, 0));

    bspline_ = BSpline(ptosControl);

    superficie = new SuperficieBarrido(perfil, normales, bspline_,100);
}