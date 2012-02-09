#include "Bodies/FirstMachine.h"

FirstMachine::FirstMachine()
{
	Vertex patch1[4] = {Vertex(2,1.25,0),Vertex(-2,1.25,0),Vertex(-2,-1.25,0),Vertex(2,-1.25,0)};
	prism_.push_back(Prism(patch1, 4, 1));
	Vertex patch2[4] = {Vertex(1.95,0.4,0),Vertex(-2,0.4,0),Vertex(-2,-0.4,0),Vertex(1.95,-0.4,0)};
	prism_.push_back(Prism(patch2, 4, 1));
	Vertex patch3[4] = {Vertex(1.95,0.2,0),Vertex(-2,0.2,0),Vertex(-2,-0.2,0),Vertex(1.95,-0.2,0)};
	prism_.push_back(Prism(patch3, 4, 1));
	Vertex patch4[4] = {Vertex(-1.2,0.9,0),Vertex(-2,0.9,0),Vertex(-2,-0.9,0),Vertex(-1.6,-0.2,0)};
	prism_.push_back(Prism(patch4, 4, 1));
}

void FirstMachine::draw()
{
    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();{
    	glScalef(0.5, 0.5, 0.5);
    	glTranslatef(-10.5,-3.5,0.5);
    	prism_[0].draw();

    	glPushMatrix();{
        	glTranslatef(0,0,2);
        	prism_[0].draw();
        }glPopMatrix();

        glPushMatrix();{
        	glTranslatef(0,0.8,1);
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

    }glPopMatrix();

}

FirstMachine::~FirstMachine()
{
}

