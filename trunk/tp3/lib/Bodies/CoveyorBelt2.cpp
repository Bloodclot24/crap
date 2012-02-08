#include "Bodies/CoveyorBelt2.h"

#include "btBulletDynamicsCommon.h"
#include "ComandoCambiarTextura.h"
#include <GL/glut.h>

CoveyorBelt::CoveyorBelt()
{
	crearSuperficie();
	texture = 0;
}

void CoveyorBelt::draw()
{
	if(texture == 0) {
		ComandoCambiarTextura comando("lad.raw");
		setTexture(comando.getTextura());
	}
    glPushMatrix();
    glColor3f(0,0,1);
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(0,0,1);
	glBegin(GL_TRIANGLE_STRIP);
	float pasosi = superficie->getVertices().size() - 1;
	float pasosj = superficie->getVertices()[0].size() - 1;
	for (int i = 0; i < pasosi ; i++) {
		for (int j = 0; j <= pasosj; j++) {
			glNormal3fv(superficie->getNormales()[i][j]);
			glTexCoord2f(i/pasosi, j /pasosj);
			glVertex3fv(superficie->getVertices()[i][j]);
			glNormal3fv(superficie->getNormales()[i + 1][j]);
			glTexCoord2f((i+1)/pasosi, j /pasosj);
			glVertex3fv(superficie->getVertices()[i + 1][j]);
		}
	}
	glEnd();
    glPopMatrix();
}

CoveyorBelt::~CoveyorBelt()
{
    delete superficie;
}

void CoveyorBelt::crearSuperficie() {
	std::vector<btVector3> perfil, normales, ptosControl;
	perfil.push_back(btVector3(0,-0.5,0));
	perfil.push_back(btVector3(0,0.5,0));
	perfil.push_back(btVector3(0,0.7,0.2));
	perfil.push_back(btVector3(0,0.6,0.2));
	perfil.push_back(btVector3(0,0.5,0.1));
	perfil.push_back(btVector3(0,-0.5,0.1));
	perfil.push_back(btVector3(0,-0.6,0.2));
	perfil.push_back(btVector3(0,-0.7,0.2));
	perfil.push_back(btVector3(0,-0.5,0));

	normales.push_back(btVector3(0, -1, -2));
	normales.push_back(btVector3(0, 1, -2));
	normales.push_back(btVector3(0, 2, 1));
	normales.push_back(btVector3(0, -1, 2));
	normales.push_back(btVector3(0, -1, 2));
	normales.push_back(btVector3(0, 1, 2));
	normales.push_back(btVector3(0, 1, 2));
	normales.push_back(btVector3(0, -2, 1));
	normales.push_back(btVector3(0, -1, -2));

	ptosControl.push_back(btVector3(-10.25, -3.75, 0));
	ptosControl.push_back(btVector3(-5.75, -4.25, 0));
	ptosControl.push_back(btVector3(-3.75, -2.25, 0));
	ptosControl.push_back(btVector3(-4.25, 2.25, 0));
	ptosControl.push_back(btVector3(-2.25, 4.25, 0));
//	ptosControl.push_back(btVector3(18.25, 3.75, 0));
	ptosControl.push_back(btVector3(2.25, 3.75, 0));
	ptosControl.push_back(btVector3(4.75, 4.25, 0));

	superficie = new SuperficieBarrido(perfil, normales, ptosControl);
}
