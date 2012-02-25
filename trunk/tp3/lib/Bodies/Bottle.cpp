#include "Bodies/Bottle.h"
#include "btBulletDynamicsCommon.h"
#include "GlobalParameters.h"

#include "GLShader.h"
#include "GLTexture.h"
#include "GLMaterial.h"

Bottle::Bottle(Bezier perfil)
{
    btCollisionShape* bottleShape = new btCylinderShapeZ(btVector3(0.1, 0.1, 0.265));

    perfil_ = perfil;

    btScalar mass = 1;
    fillLevel = 0;
    label = false;
    labelTime = 0;

    btVector3 fallInertia(0,0,0);

    btTransform startTransform;
    startTransform.setIdentity();

    bottleShape->calculateLocalInertia(mass,fallInertia);

    startTransform.setIdentity();

    startTransform.setOrigin(btVector3(btScalar(0),
                                       btScalar(0),
                                       btScalar(0)));

    btDefaultMotionState* bottleMotionState = new btDefaultMotionState(startTransform);

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI3(mass,bottleMotionState,bottleShape,fallInertia);
    rigidBody_ = new btRigidBody(fallRigidBodyCI3);
    rigidBody_->setFriction(0.5);
    rigidBody_->setDamping(0.1, 0.1);

    crearSuperficie();
}

void Bottle::crearSuperficie() {

    superficie = new SuperficieRevolucion(perfil_, BOTTLE_ROTATIONS, BOTTLE_STEP);
    height_ = 26.5;
}

bool Bottle::fill(float quantity)
{
    bool full = false;
    fillLevel += quantity;
    if(fillLevel>0.8) {
        fillLevel = 0.8;
        full = true;
    }
    return !full;
}

bool Bottle::putLabel(float step) {
    labelTime += step;
    if(labelTime > 0.2)
        label = true;
    return label;
}

void Bottle::draw()
{
    GLTexture::bind("etiqueta");

    GLShader::pushProgram("bottle");{
        GLMaterial::push("glass");{

            GLShader::setUniform("fillLevel", fillLevel);
            GLShader::setUniform("label", label);

            glPushMatrix();{

                glColor3f(1, 1, 1);

                btVector3 position = getPosition();

                btTransform trans;
                rigidBody_->getMotionState()->getWorldTransform(trans);

                btVector3 axis = trans.getRotation().getAxis();

                glTranslatef(position[0],
                             position[1],
                             position[2]);

                glRotatef(trans.getRotation().getAngle()*360/6.2832f,
                          axis.getX(),
                          axis.getY(),
                          axis.getZ());

                glScalef(0.02,0.02,0.02);
                glTranslatef(0,0,-height_/2);

                superficie->draw();
            }glPopMatrix();

        }GLMaterial::pop();

    }GLShader::popProgram();
}

Bottle::~Bottle()
{
    delete superficie;
}

