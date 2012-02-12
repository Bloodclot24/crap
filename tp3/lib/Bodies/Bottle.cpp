#include "Bodies/Bottle.h"
#include "btBulletDynamicsCommon.h"

#include "GLShader.h"
#include "GLTexture.h"

Bottle::Bottle()
{
    btCollisionShape* bottleShape = new btCylinderShapeZ(btVector3(0.1*BOTTLE_SCALE, 0.1*BOTTLE_SCALE, 0.265*BOTTLE_SCALE));

    btScalar mass = 1;
    fillLevel = 0;

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
    rigidBody_ = new btRigidBody(fallRigidBodyCI3);
    rigidBody_->setFriction(0.5);
    rigidBody_->setDamping(0.7, 0.7);
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
    height_ = 26.5;
}

void Bottle::fill(float quantity)
{
    fillLevel += quantity;
    if(fillLevel>1)
        fillLevel = 1;
}

void Bottle::draw()
{

    GLTexture::bind("etiqueta");
    GLShader::pushProgram("bottle");

    GLShader::setUniform("fillLevel", fillLevel);

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

        glScalef(0.02*BOTTLE_SCALE,0.02*BOTTLE_SCALE,0.02*BOTTLE_SCALE);
        glTranslatef(0,0,-height_/2);
    	glBegin( GL_TRIANGLE_STRIP);
    	float pasosi = superficie->getVertices().size() - 1;
    	float pasosj = superficie->getVertices()[0].size() - 1;
    	for (int i = 0; i < pasosi ; i++) {
            for (int j = 0; j <= pasosj; j++) {
                float height = superficie->getVertices()[i][j][2];
                glNormal3fv(superficie->getNormales()[i][j]);
                glTexCoord2f(i/pasosi,superficie->getVertices()[i][j][2]/height_);
                glVertex3fv(superficie->getVertices()[i][j]);
                glNormal3fv(superficie->getNormales()[fmod(i + 1, pasosi)][j]);
                glTexCoord2f((i+1)/pasosi,superficie->getVertices()[i][j][2]/height_);
                glVertex3fv(superficie->getVertices()[fmod(i + 1, pasosi)][j]);
            }
    	}
    	glEnd();

    }glPopMatrix();

    GLShader::popProgram();
}

Bottle::~Bottle()
{
    delete superficie;
}

