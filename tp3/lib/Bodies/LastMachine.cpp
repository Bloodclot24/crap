#include "Bodies/LastMachine.h"

LastMachine::LastMachine()
{
	Vertex patch0[4] = {Vertex(3,1.25,0),Vertex(-3,1.25,0),Vertex(-3,-1.25,0),Vertex(3,-1.25,0)};
	prism_.push_back(Prism(patch0, 4, 1));
	Vertex patch1[4] = {Vertex(2.95,0.5,0),Vertex(-2.95,0.5,0),Vertex(-2.95,-0.5,0),Vertex(2.95,-0.5,0)};
	prism_.push_back(Prism(patch1, 4, 1));
	Vertex patch2[4] = {Vertex(2.95,0.2,0),Vertex(-2.95,0.2,0),Vertex(-2.95,-0.2,0),Vertex(2.95,-0.2,0)};
	prism_.push_back(Prism(patch2, 4, 1));
	Vertex patch3[4] = {Vertex(2.95,0.2,0),Vertex(-1.5,0.2,0),Vertex(-1.5,-0.8,0),Vertex(2.95,-0.8,0)};
	prism_.push_back(Prism(patch3, 4, 1));
	Vertex patch4[4] = {Vertex(2.95,1.2,0),Vertex(2.5,1.2,0),Vertex(2.5,-1.2,0),Vertex(2.95,-1.2,0)};
	prism_.push_back(Prism(patch4, 4, 1));
	Vertex patch5[4] = {Vertex(1,1.2,0),Vertex(-2.95,1.2,0),Vertex(-2.95,-1.2,0),Vertex(1,-1.2,0)};
	prism_.push_back(Prism(patch5, 4, 1));
	Vertex patch6[4] = {Vertex(2.5,1.2,0),Vertex(1,1.2,0),Vertex(1,0,0),Vertex(2.5,0,0)};
	prism_.push_back(Prism(patch6, 4, 1));
/*
	Vertex patch1[4] = {Vertex(2,1.25,0),Vertex(-3,1.25,0),Vertex(-3,-1.25,0),Vertex(2,-1.25,0)};
	prism_.push_back(Prism(patch1, 4, 1));
	Vertex patch2[4] = {Vertex(1.95,0.5,0),Vertex(-2.95,0.5,0),Vertex(-2.95,-0.5,0),Vertex(1.95,-0.5,0)};
	prism_.push_back(Prism(patch2, 4, 1));
	Vertex patch3[4] = {Vertex(1.95,0.2,0),Vertex(-2.95,0.2,0),Vertex(-2.95,-0.2,0),Vertex(1.95,-0.2,0)};
	prism_.push_back(Prism(patch3, 4, 1));
	Vertex patch4[4] = {Vertex(1.95,0.2,0),Vertex(-1.5,0.2,0),Vertex(-1.5,-0.8,0),Vertex(1.95,-0.8,0)};
	prism_.push_back(Prism(patch4, 4, 1));
	*/
	crearRampa();
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
//        glRotatef(-90,0,0,1);
//        glRotatef(90,1,0,0);
//        rampa->draw();
    }glPopMatrix();

}

void LastMachine::crearRampa() {
	std::vector<btVector3> perfil, normales, ptosControl;
    //rampa = new SuperficieBarrido(perfil, normales, ptosControl);
}

LastMachine::~LastMachine()
{
	//delete rampa;
}

