#include "Bodies/LabelMachine.h"

LabelMachine::LabelMachine(): cylinder_(0.25,0.55)
{
	btVector3 patch0[4] = {btVector3(0.5,0.5,0),btVector3(-0.5,0.5,0),btVector3(-0.5,-0.5,0),btVector3(0.5,-0.5,0)};
	prism_.push_back(Prism(patch0, 4, 1));
	btVector3 patch1[4] = {btVector3(0.7,0.7,0),btVector3(-0.7,0.7,0),btVector3(-0.7,-0.7,0),btVector3(0.7,-0.7,0)};
	prism_.push_back(Prism(patch1, 4, 2));
	btVector3 patch2[4] = {btVector3(0.05,0.6,0),btVector3(-0.06,0.5,0),btVector3(-0.06,-0.5,0),btVector3(0.05,-0.6,0)};
	prism_.push_back(Prism(patch2, 4, 0.1));
	subiendo = false;
	level = 0.2;
}

void LabelMachine::draw()
{
    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();{
    	glScalef(0.5, 0.5, 0.5);
    	glTranslatef(-2.6,5.2,0.5);
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
        	glTranslatef(0,-1.5,0.2);
        	glColor3f(1,1,0);
        	cylinder_.draw();

        	glScalef(0.9, 0.9, 1.4);
        	glTranslatef(0,0,-0.5 + level*2.4);
        	glColor3f(0.6,0.6,0);
        	cylinder_.draw();
        }glPopMatrix();
    }glPopMatrix();

}

bool LabelMachine::process(Bottle* bottle, float step) {
	if(level > 0 && !subiendo)
		level -= step;
	else if(bottle->putLabel(step)) {
		level += step;
		subiendo = level < 0.2;
	}
	return level <= 0.2;
}

LabelMachine::~LabelMachine()
{
}


