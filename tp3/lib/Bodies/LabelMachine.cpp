#include "Bodies/LabelMachine.h"

LabelMachine::LabelMachine(): cylinder_(0.25,1)
{
	btVector3 patch1[4] = {btVector3(0.5,0.5,0),btVector3(-0.5,0.5,0),btVector3(-0.5,-0.5,0),btVector3(0.5,-0.5,0)};
	prism_.push_back(Prism(patch1, 4, 1));
	btVector3 patch2[4] = {btVector3(0.7,0.7,0),btVector3(-0.7,0.7,0),btVector3(-0.7,-0.7,0),btVector3(0.7,-0.7,0)};
	prism_.push_back(Prism(patch2, 4, 2));
	btVector3 patch3[4] = {btVector3(0.05,0.6,0),btVector3(-0.06,0.5,0),btVector3(-0.06,-0.5,0),btVector3(0.05,-0.6,0)};
	prism_.push_back(Prism(patch3, 4, 0.1));
}

void LabelMachine::draw()
{
    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();{
    	glScalef(0.5, 0.5, 0.5);
    	glTranslatef(-2.5,5.2,0.5);
    	prism_[0].draw();
    	glTranslatef(0,0,1.5);
    	prism_[1].draw();

    	glPushMatrix();{
        	glTranslatef(0.3,-1.1,0.5);
        	prism_[2].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(-0.3,-1.1,0.5);
        	prism_[2].draw();
        }glPopMatrix();
        glPushMatrix();{
        	glTranslatef(0,-1.5,-0.3);
        	cylinder_.draw();
        }glPopMatrix();
    }glPopMatrix();

}

LabelMachine::~LabelMachine()
{
}

