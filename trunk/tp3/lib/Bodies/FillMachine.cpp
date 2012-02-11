#include "Bodies/FillMachine.h"
#include <GL/gl.h>

FillMachine::FillMachine(): cylinder_(0.8,0.4), sphere_(0.8)
{
	btVector3 patch0[4] = {btVector3(0.5,0.5,0),btVector3(-0.5,0.5,0),btVector3(-0.5,-0.5,0),btVector3(0.5,-0.5,0)};
	prism_.push_back(Prism(patch0, 4, 1));
	btVector3 patch1[4] = {btVector3(0.05,0,0.05),btVector3(-0.05,0,0.05),btVector3(-0.05,0,-0.05),btVector3(0.05,0,-0.05)};
	prism_.push_back(Prism(patch1, 4, 4));
	prism_.push_back(Prism(patch1, 4, 0.1));
	crearManguera();
}

void FillMachine::draw()
{
    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();{
    	glScalef(0.5, 0.5, 0.5);
    	glTranslatef(1,5.4,0.5);
    	prism_[0].draw();
    	glTranslatef(0,0,0.5);
    	sphere_.draw();
    	cylinder_.draw();
    	glTranslatef(0,0,0.4);
    	sphere_.draw();
    	glPushMatrix();{
    		glTranslatef(0,0,1);
    		glScalef(0.4, 0.4, 0.6);
    		prism_[0].draw();
    	}glPopMatrix();
    	glTranslatef(0,-1.1,1);
    	glScalef(0.4,0.4,0.4);
    	glPushMatrix();{
    		glTranslatef(-0.3,0.3,-0.3);
    		prism_[1].draw();
    	}glPopMatrix();
    	glPushMatrix();{
    		glTranslatef(-0.3,0.3,0.3);
    		prism_[1].draw();
    	}glPopMatrix();
    	glPushMatrix();{
    		glTranslatef(0.3,0.3,-0.3);
    		prism_[1].draw();
    	}glPopMatrix();
    	glPushMatrix();{
    		glTranslatef(0.3,0.3,0.3);
    		prism_[1].draw();
    	}glPopMatrix();
    	glRotatef(-90,0,0,1);
    	glRotatef(90,1,0,0);
    	glColor3f(1, 1, 0);
    	manguera->draw();
    }glPopMatrix();

}

FillMachine::~FillMachine()
{
}

void FillMachine::crearManguera() {
	std::vector<btVector3> perfil, ptosControl;
	float radio = 0.3;
	int segmentos = 10;
    for (float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos)
    	perfil.push_back(btVector3(0, cos(i)*radio, sin(i)*radio));

	ptosControl.push_back(btVector3(-4, 0, 0));
	ptosControl.push_back(btVector3(-1, 0, 0));
	ptosControl.push_back(btVector3(1, 0, 0));
	ptosControl.push_back(btVector3(1, -2, 0));

    manguera = new SuperficieBarrido(perfil, perfil, ptosControl);
}
