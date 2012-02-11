#include "Bodies/LastMachine.h"
#include <GL/gl.h>

LastMachine::LastMachine()
{
	btVector3 patch0[4] = {btVector3(3,1.25,0),btVector3(-3,1.25,0),btVector3(-3,-1.25,0),btVector3(3,-1.25,0)};
	prism_.push_back(Prism(patch0, 4, 1));
	btVector3 patch1[4] = {btVector3(2.95,0.5,0),btVector3(-2.95,0.5,0),btVector3(-2.95,-0.5,0),btVector3(2.95,-0.5,0)};
	prism_.push_back(Prism(patch1, 4, 1));
	btVector3 patch2[4] = {btVector3(2.95,0.2,0),btVector3(-2.95,0.2,0),btVector3(-2.95,-0.2,0),btVector3(2.95,-0.2,0)};
	prism_.push_back(Prism(patch2, 4, 1));
	btVector3 patch3[4] = {btVector3(2.95,0.2,0),btVector3(-1.5,0.2,0),btVector3(-1.5,-0.8,0),btVector3(2.95,-0.8,0)};
	prism_.push_back(Prism(patch3, 4, 1));
	btVector3 patch4[4] = {btVector3(2.95,1.2,0),btVector3(2.5,1.2,0),btVector3(2.5,-1.2,0),btVector3(2.95,-1.2,0)};
	prism_.push_back(Prism(patch4, 4, 1));
	btVector3 patch5[4] = {btVector3(1,1.2,0),btVector3(-2.95,1.2,0),btVector3(-2.95,-1.2,0),btVector3(1,-1.2,0)};
	prism_.push_back(Prism(patch5, 4, 1));
	btVector3 patch6[4] = {btVector3(2.5,1.2,0),btVector3(1,1.2,0),btVector3(1,0,0),btVector3(2.5,0,0)};
	prism_.push_back(Prism(patch6, 4, 1));

	createRamp();
}

void LastMachine::draw()
{
    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();{
    	glScalef(0.5, 0.5, 0.5);
    	glTranslatef(8.5,5.6,0.5);
    	prism_[0].draw();

    	glPushMatrix();{
        	glTranslatef(0,0,2);
        	prism_[0].draw();
        	glTranslatef(0,0,2);
        	prism_[0].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,0.7,1);
        	prism_[1].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,-1,1);
        	prism_[2].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,0,1);
        	prism_[3].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,0,3);
        	prism_[4].draw();
        	prism_[5].draw();
        	prism_[6].draw();
        }glPopMatrix();

        drawRamp();
    }glPopMatrix();

}

void LastMachine::drawRamp() {
	glScalef(0.6, 0.6, 0.6);
	glPushMatrix();{
		glTranslatef(3, -5, 2.2);
		glRotatef(35, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		ramp_[0].draw();
	} glPopMatrix();
	glPushMatrix();{
		glTranslatef(4, -5, 2.3);
		glRotatef(35, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		ramp_[1].draw();
	} glPopMatrix();
	glPushMatrix();{
		glTranslatef(2, -5, 2.3);
		glRotatef(35, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		ramp_[1].draw();
	} glPopMatrix();
	glPushMatrix();{
		glTranslatef(3, -8.8, 0);
		glRotatef(12, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		ramp_[2].draw();
	} glPopMatrix();
	glPushMatrix();{
		glTranslatef(4, -8.8, 0.1);
		glRotatef(12, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		ramp_[3].draw();
	} glPopMatrix();
	glPushMatrix();{
		glTranslatef(2, -8.8, 0.1);
		glRotatef(12, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		ramp_[3].draw();
	} glPopMatrix();
}

void LastMachine::createRamp() {
	btVector3 patch0[4] = {btVector3(3.5,1,0),btVector3(-3.5,1,0),btVector3(-3.5,-1,0),btVector3(3.5,-1,0)};
	ramp_.push_back(Prism(patch0, 4, 0.01));
	btVector3 patch1[4] = {btVector3(3.5,0,0.1),btVector3(-3.5,0,0.1),btVector3(-3.5,0,-0.1),btVector3(3.5,0,-0.1)};
	ramp_.push_back(Prism(patch1, 4, 0.01));
	btVector3 patch2[4] = {btVector3(1,1,0),btVector3(-1,1,0),btVector3(-1,-1,0),btVector3(1,-1,0)};
	ramp_.push_back(Prism(patch2, 4, 0.01));
	btVector3 patch3[4] = {btVector3(1,0,0.1),btVector3(-1,0,0.1),btVector3(-1,0,-0.1),btVector3(1,0,-0.1)};
	ramp_.push_back(Prism(patch3, 4, 0.01));
}

LastMachine::~LastMachine()
{
}

