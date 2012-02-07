#include "Bodies/Bottle.h"
#include "btBulletDynamicsCommon.h"
#include "ComandoCambiarTextura.h"

#define ESCALA 2

Bottle::Bottle():cylinder_(0.25, 1)
{
    btCollisionShape* bottleShape = new btCylinderShapeZ(btVector3(0.1*ESCALA, 0.1*ESCALA, 0.265*ESCALA));

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
    fallRigidBodyCI3.m_restitution = 0.5;
    rigidBody_ = new btRigidBody(fallRigidBodyCI3);
    rigidBody_->setFriction(1);
    crearSuperficie();
}

void Bottle::crearSuperficie() {
	//La botella mide 5 de radio mayor y 26.5 de alto, sin tapa
	std::vector<btVector3> ptos;
	ptos.push_back(btVector3(0, 0, 0.8));
	ptos.push_back(btVector3(1.3, 0, 0.8));
	ptos.push_back(btVector3(2.5, 0, -0.5));
	ptos.push_back(btVector3(3, 0, 0.3));
	ptos.push_back(btVector3(6, 0, 3));
	ptos.push_back(btVector3(1.5, 0, 2));
	ptos.push_back(btVector3(4, 0, 11));
	ptos.push_back(btVector3(4.8, 0, 20));
	ptos.push_back(btVector3(1.5, 0, 18));
	ptos.push_back(btVector3(1, 0, 24));
	ptos.push_back(btVector3(1.5, 0, 24.5));
	ptos.push_back(btVector3(1.3, 0, 25));
	ptos.push_back(btVector3(1.3, 0, 26.5));
	superficie = new SuperficieRevolucion(ptos);
	upTextureBound = 17;
	downTextureBound = 11;
	ComandoCambiarTextura comando("lad.raw");
	setTexture(comando.getTextura());
}

void Bottle::draw()
{
    glPushMatrix();{

        glColor3f(1, 1, 1);

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

        glTranslatef(0,0,-0.265*ESCALA); //?
        glScalef(0.02*ESCALA,0.02*ESCALA,0.02*ESCALA);
        //superficie->draw();
        glBindTexture (GL_TEXTURE_2D, texture);
    	glBegin( GL_TRIANGLE_STRIP);
    	for (int i = 0; i < superficie->getVertices().size() ; i++) {
    		for (int j = 0; j < superficie->getVertices()[i].size(); j++) {
    			float height = superficie->getVertices()[i][j][2];

    			glNormal3fv(superficie->getNormales()[i][j]);
    			if(downTextureBound <= height && height <= upTextureBound)
       					glTexCoord2f(i/(float)superficie->getVertices().size(),(height - downTextureBound)/(upTextureBound - downTextureBound));
    			glVertex3fv(superficie->getVertices()[i][j]);

    			glNormal3fv(superficie->getNormales()[fmod(i + 1, superficie->getVertices().size())][j]);
    			if(downTextureBound <= height && height <= upTextureBound)
    					glTexCoord2f((i+1)/(float)superficie->getVertices().size(), (height - downTextureBound)/(upTextureBound - downTextureBound));
    			glVertex3fv(superficie->getVertices()[fmod(i + 1, superficie->getVertices().size())][j]);
    		}
    	}
    	glEnd();

    }glPopMatrix();
}

Bottle::~Bottle()
{
    delete superficie;
}

