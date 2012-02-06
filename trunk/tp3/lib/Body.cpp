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


btVector3 Body::getPosition()
{
    btTransform transformation;
    rigidBody_->getMotionState()->getWorldTransform(transformation);

    return transformation.getOrigin();
}