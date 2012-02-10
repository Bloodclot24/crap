#include "Body.h"

btRigidBody* Body::getRigidBody()
{
    return rigidBody_;
}

Body::Body()
{
}

void Body::setPosition(float x, float y, float z)
{
    btTransform transformation;
    transformation.setIdentity();
    transformation.setOrigin(btVector3(btScalar(x),
                                       btScalar(y),
                                       btScalar(z)));

    btDefaultMotionState* newMotionState = new btDefaultMotionState(transformation);
    rigidBody_->setMotionState(newMotionState);
}


void Body::setRotation(float rotx, float roty, float rotz)
{
    btTransform transformation;
    transformation.setIdentity();
    transformation.setOrigin(getPosition());
    transformation.setRotation(btQuaternion(rotx, roty, rotz, 1));

    btDefaultMotionState* newMotionState = new btDefaultMotionState(transformation);
    rigidBody_->setMotionState(newMotionState);
}

btVector3 Body::getPosition()
{
    btTransform transformation;
    rigidBody_->getMotionState()->getWorldTransform(transformation);

    return transformation.getOrigin();
}

void Body::setTexture(GLuint t){
  texture = t;
}
