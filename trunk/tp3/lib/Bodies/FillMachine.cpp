#include "Bodies/FillMachine.h"

FillMachine::FillMachine(): cylinder_(1,0.5), sphere_(1)
{
	Vertex patch1[4] = {Vertex(0.5,0.5,0),Vertex(-0.5,0.5,0),Vertex(-0.5,-0.5,0),Vertex(0.5,-0.5,0)};
	prism_.push_back(Prism(patch1, 4, 1));
	Vertex patch2[4] = {Vertex(0.7,0.7,0),Vertex(-0.7,0.7,0),Vertex(-0.7,-0.7,0),Vertex(0.7,-0.7,0)};
	prism_.push_back(Prism(patch2, 4, 2));
	Vertex patch3[4] = {Vertex(0.05,0.6,0),Vertex(-0.06,0.5,0),Vertex(-0.06,-0.5,0),Vertex(0.05,-0.6,0)};
	prism_.push_back(Prism(patch3, 4, 0.1));
	crearManguera();
}

void FillMachine::draw()
{
    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();{
    	glScalef(0.5, 0.5, 0.5);
    	glTranslatef(1,5.7,0.5);
    	prism_[0].draw();
    	glTranslatef(0,0,1);
    	sphere_.draw();
    	cylinder_.draw();
    	glTranslatef(0,0,0.5);
    	sphere_.draw();
    	glTranslatef(0,-1.5,0.5);
    	glRotatef(-90,0,0,1);
    	glRotatef(90,1,0,0);
    	glScalef(0.4,0.4,0.4);
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
