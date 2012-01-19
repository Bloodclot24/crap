#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "TP3.h"

#include "Primitives/Cube.h"
#include "Primitives/Cylinder.h"

TP3::TP3()
{
    windowWidth_ = 1;
    windowHeight_ = 1;
    dynamicsWorld_ = NULL;
}

void TP3::initialize()
{
    initializePhysics();

    for(int i=0; i<5; ++i){
        bottles[i].setPosition(0,0,5*(i+1));
        addBody(&bottles[i]);
    }

    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_NORMALIZE);
}

void TP3::setUpGlContext()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, 
                   (GLfloat)windowWidth_/(GLfloat)windowHeight_, 
                   0.10, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, -6, 2,
              0,  0, 0,
              0,  1, 0);
}

void TP3::updateScene()
{
    dynamicsWorld_->stepSimulation(1.0/30, 10);
}

void TP3::renderScene()
{

    glBegin(GL_QUADS);{
        glColor3f(1, 0, 0);

        glNormal3f(0,0,1);

        glVertex3f(-10, -10, 0);
        glVertex3f(-10,  10, 0);
        glVertex3f( 10,  10, 0);
        glVertex3f( 10, -10, 0);

    }glEnd();

    for(int i=0; i<5; ++i)
        bottles[i].draw();

}

void TP3::handleDisplay()
{
    setUpGlContext();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateScene();

    renderScene();

    glutSwapBuffers();
}

void TP3::handleReshape(int width, int height)
{
    windowWidth_  = width;
    windowHeight_ = height;
}

void TP3::handleKeyboard(unsigned char key, int x, int y)
{

}

void TP3::initializePhysics()
{
    // Inicializacion del motor de fisica
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
 
    btDefaultCollisionConfiguration* 
        collisionConfiguration = new btDefaultCollisionConfiguration();

    btCollisionDispatcher* 
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
    btSequentialImpulseConstraintSolver* 
        solver = new btSequentialImpulseConstraintSolver;
 
    dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher, 
                                                 broadphase, 
                                                 solver, 
                                                 collisionConfiguration);

    dynamicsWorld_->setGravity(btVector3(0,0,-10));

    // Definimos plano del suelo - Cuerpo rigido estatico (masa=0)
    // parametros: normal {x,y,z} , espesor o altura
    btCollisionShape* 
        groundShape = new btStaticPlaneShape(btVector3(0, 0, 1), 2);


    btDefaultMotionState* groundMotionState = 
        new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
                                             btVector3(0, 0, -2)));
    // Los 2 vectores representan la orientacion (x,y,z,w) y
    // traslacion (x,y,z) del objeto suelo, traslacion es (0,0,-2)
    // para compensar el espesor que es 2, asi el lado superior del
    // piso queda en Z=0

    btRigidBody::btRigidBodyConstructionInfo 
        groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0,0,0));

    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

    groundRigidBody->setFriction(1.0);

    dynamicsWorld_->addRigidBody(groundRigidBody);
}

void TP3::timerCallback(int value)
{
    glutPostRedisplay();
}

void TP3::addBody(Body* body)
{
    dynamicsWorld_->addRigidBody(body->getRigidBody());
}
