#include "Bodies/Pack.h"
#include <GL/gl.h>

Pack::Pack() {
    btCollisionShape* bottleShape = new btBoxShape(btVector3(0.16, 0.16, 0.265));

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
    rigidBody_ = new btRigidBody(fallRigidBodyCI3);
    rigidBody_->setFriction(0.5);
    rigidBody_->setDamping(0.7, 0.7);
}

Pack::~Pack() {
}

void Pack::draw() {
	glPushMatrix(); {
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

		glTranslatef(0,0,-0.265/2);

		glPushMatrix(); {
			glTranslatef(0.08,0.08,0);
			bottles_[0]->draw();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.08,0.08,0);
			bottles_[1]->draw();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.08,-0.08,0);
			bottles_[2]->draw();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.08,-0.08,0);
			bottles_[3]->draw();
		} glPopMatrix();
	} glPopMatrix();
}

void Pack::addBottle(Bottle* bottle) {
	bottle->setPosition(0,0,0);
	bottles_.push_back(bottle);
}

int Pack::getBottlesCount() {
	return bottles_.size();
}
