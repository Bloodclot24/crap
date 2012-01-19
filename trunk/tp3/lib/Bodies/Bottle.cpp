#include "Bodies/Bottle.h"

#include "btBulletDynamicsCommon.h"

Bottle::Bottle():cylinder_(0.25, 1)
{
    btCollisionShape* bottleShape = new btCylinderShapeZ(btVector3(0.25, 0.25, 0.5));

    btScalar mass = 1;

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
    fallRigidBodyCI3.m_restitution = 0.5;
    rigidBody_ = new btRigidBody(fallRigidBodyCI3);
    rigidBody_->setFriction(1);
}

void Bottle::draw()
{

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
      
        glTranslatef(0, 0, -0.5);
        cylinder_.draw();

    }glPopMatrix();
}

Bottle::~Bottle()
{
    
}

