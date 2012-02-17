#include "Bodies/LastMachine.h"
#include <GL/gl.h>

LastMachine::LastMachine()
{
	btVector3 patch0[4] = {btVector3(3,1.25,0),btVector3(-3,1.25,0),btVector3(-3,-1.25,0),btVector3(3,-1.25,0)};
	prism_.push_back(Prism(patch0, 4, 1));
	btVector3 patch1[4] = {btVector3(2.95,0.5,0),btVector3(-2.95,0.5,0),btVector3(-2.95,-0.5,0),btVector3(2.95,-0.5,0)};
	prism_.push_back(Prism(patch1, 4, 1.4));
	btVector3 patch2[4] = {btVector3(2.95,0.2,0),btVector3(-2.95,0.2,0),btVector3(-2.95,-0.2,0),btVector3(2.95,-0.2,0)};
	prism_.push_back(Prism(patch2, 4, 1.4));
	btVector3 patch3[4] = {btVector3(2.95,0.2,0),btVector3(-1.5,0.2,0),btVector3(-1.5,-0.8,0),btVector3(2.95,-0.8,0)};
	prism_.push_back(Prism(patch3, 4, 1.4));
	btVector3 patch4[4] = {btVector3(2.95,1.2,0),btVector3(2.5,1.2,0),btVector3(2.5,-1.2,0),btVector3(2.95,-1.2,0)};
	prism_.push_back(Prism(patch4, 4, 1.4));
	btVector3 patch5[4] = {btVector3(1,1.2,0),btVector3(-2.95,1.2,0),btVector3(-2.95,-1.2,0),btVector3(1,-1.2,0)};
	prism_.push_back(Prism(patch5, 4, 1.4));
	btVector3 patch6[4] = {btVector3(2.5,1.2,0),btVector3(1,1.2,0),btVector3(1,0,0),btVector3(2.5,0,0)};
	prism_.push_back(Prism(patch6, 4, 1.4));

	createRamp();
}

void LastMachine::draw()
{
    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();{
    	glScalef(0.5, 0.5, 0.5);
    	glTranslatef(8.5,5.6,0);
    	glPushMatrix();{
    		glTranslatef(0,0,0.5);
    		prism_[0].draw();
        	glTranslatef(0,0,3.8);
        	prism_[0].draw();
    	}glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,0.7,1.7);
        	prism_[1].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,-1,1.7);
        	prism_[2].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,0,1.7);
        	prism_[3].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,0,3.1);
        	prism_[4].draw();
        	prism_[5].draw();
        	prism_[6].draw();
        }glPopMatrix();

    }glPopMatrix();
    drawRamp();

}

void LastMachine::drawRamp() {

	glPushMatrix();{
		glTranslatef(5.15, 1.35, 0.6);
		glRotatef(35, 1, 0, 0);
		ramp_[0].draw();
	} glPopMatrix();
	glPushMatrix();{
		glTranslatef(4.85, 1.35, 0.63);
		glRotatef(35, 1, 0, 0);
		ramp_[1].draw();
	} glPopMatrix();
	glPushMatrix();{
		glTranslatef(5.45, 1.35, 0.63);
		glRotatef(35, 1, 0, 0);
		ramp_[1].draw();
	} glPopMatrix();

        btTransform trans;
        rigidBody_->getMotionState()->getWorldTransform(trans);
        btVector3 axis = trans.getRotation().getAxis();

        printf("Rotation: %f, %f, %f : %f\n", axis.getX(), axis.getY(), axis.getZ(), trans.getRotation().getAngle());

}

void LastMachine::createRamp() {

    btVector3 patch0[4] = {btVector3(0.3,-1.05,0),btVector3(0.3,1.05,0),btVector3(-0.3,1.05,0),btVector3(-0.3,-1.05,0)};
    ramp_.push_back(Prism(patch0, 4, 0.01));
    btVector3 patch1[4] = {btVector3(0,1.05,0.03),btVector3(0,1.05,-0.03),btVector3(0,-1.05,-0.03),btVector3(0,-1.05,0.03)};
    ramp_.push_back(Prism(patch1, 4, 0.01));

    btCollisionShape* prismShape = new btBoxShape(btVector3(3.5,2,0.2));

    btScalar mass = 0;

    btVector3 fallInertia(0,0,0);

    btTransform startTransform;
    startTransform.setIdentity();

    prismShape->calculateLocalInertia(mass,fallInertia);

    startTransform.setIdentity();

    startTransform.setOrigin(btVector3(5.15, 1.35, 0.4));
    
    startTransform.setRotation(btQuaternion(35/2.0*3.14/180.0,0,0,1));

    btDefaultMotionState* bottleMotionState = new btDefaultMotionState(startTransform);

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI3(mass,bottleMotionState,prismShape,fallInertia);
    rigidBody_ = new btRigidBody(fallRigidBodyCI3);
    rigidBody_->setFriction(0);
}

LastMachine::~LastMachine()
{
}

