#include "Bodies/CoveyorBelt2.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLMaterial.h"
#include "GlobalParameters.h"

#include "btBulletDynamicsCommon.h"
#include <GL/glut.h>
#include <math.h>

CoveyorBelt::CoveyorBelt(BSpline curve)
{
    bspline_ = curve;
    crearSuperficie();
    displacement = 0;
}

void CoveyorBelt::draw()
{

    glColor3f(1, 1, 1);
    GLTexture::bind("cinta");

    GLShader::pushProgram("belt");{

        GLShader::setUniform("displacement", displacement);

        glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(0,0,1);

        superficie->draw();

        glPopMatrix();

    }GLShader::popProgram();
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

    superficie = new SuperficieBarrido(perfil, normales, bspline_,BELT_STEP);
}
