#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GLShader.h"
#include "GLTexture.h"
#include "Primitives/Cube.h"
#include "Primitives/Cylinder.h"
#include "Curves/StraightLine.h"
#include "Bodies/FirstMachine.h"
#include "Bodies/LastMachine.h"
#include "Bodies/LabelMachine.h"
#include "Bodies/FillMachine.h"
#include "TP3.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define SPEED 2.0

TP3::TP3()
{
    windowWidth_ = 1;
    windowHeight_ = 1;
    dynamicsWorld_ = NULL;

    StraightLine line(btVector3(-3, -3, 1), btVector3(3, 5, 0));

    belt_ = new CoveyorBelt();

    bottleInterval_ = 27.0*5.0/SPEED;
    nextBottle_ = 0;
    firstBottle_ = 0;

    machines[0] = new FirstMachine();
    machines[1] = new LastMachine();
    machines[2] = new LabelMachine();
    machines[3] = new FillMachine();

    xrot_ = yrot_ = zrot_ = 0;

    xtrans_ = 0;
    ytrans_ = -6;
    ztrans_ = 2;

    stopAnimation = false;
}

void TP3::initialize()
{
    initializePhysics();

    //Cargo texturas
    GLTexture::load("lad.raw", "ladrillos");
    GLTexture::load("chapaDoble.raw", "chapa");
    GLTexture::load("cinta.raw", "cinta");
    GLTexture::load("eti.raw", "etiqueta");

    //Cargo VShaders
    GLShader::loadVShader("shaders/normal.vert", "normal");
    GLShader::loadVShader("shaders/light.vert", "light");
    
    //Cargo FShaders
    GLShader::loadFShader("shaders/base.frag", "base");
    GLShader::loadFShader("shaders/texture.frag", "texture");
    GLShader::loadFShader("shaders/light.frag", "light");
    GLShader::loadFShader("shaders/belt.frag", "belt");
    GLShader::loadFShader("shaders/bottle.frag", "bottle");

    //Creo los programas
    //const char* normalVShader[] = {"normal", NULL};
    const char* lightVShader[]  = {"light", NULL};

    const char* normalFShader[] = {"base", "texture", "light", NULL};
    const char* beltFShader[]   = {"base", "belt",    "light", NULL};
    const char* bottleFShader[] = {"base", "bottle",  "light", NULL};

    GLShader::createProgram("normal", lightVShader, normalFShader);
    GLShader::createProgram("belt",   lightVShader, beltFShader);
    GLShader::createProgram("bottle", lightVShader, bottleFShader);

    GLShader::pushProgram("normal");

    //Activo iluminacion
    glEnable(GL_LIGHT0);

    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    GLfloat ambient[] = { 0.4f, 0.4f, 0.4f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    GLfloat position[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
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

    gluLookAt(xtrans_, ytrans_, ztrans_,
              0,  0, 0,
              0,  1, 0);

    glRotatef(xrot_, 1, 0, 0);
    glRotatef(yrot_, 0, 1, 0);
    glRotatef(zrot_, 0, 0, 1);
}

void TP3::updateScene()
{

    if(!stopAnimation){
        dynamicsWorld_->stepSimulation(1.0/30.0, 10);
        belt_->advance(0.01*2*SPEED);
    
        nextBottle_-=1.0;

        if(nextBottle_ <= 0){
            nextBottle_ = bottleInterval_;
            bottles_.push_back(new Bottle());
            bottlesPositions_.push_back(0);

        }

        for(unsigned i=firstBottle_;i<bottles_.size();i++){
            btVector3 pos     = belt_->getPosition(bottlesPositions_[i]);
            btVector3 tangent = belt_->getTangent(bottlesPositions_[i]);
            bottlesPositions_[i] += 0.0005*2*SPEED;
            if(bottlesPositions_[i] >= 1){
                firstBottle_ = i+1;
                bottles_[i]->setPosition(5,2,2);
                addBody(bottles_[i]);
            }

            else{ 
                bottles_[i]->setPosition(pos.x(), pos.y(), pos.z()+0.265);
                bottles_[i]->setRotation(0,0,acos(tangent.normalize().dot(btVector3(1,0,0))));
                bottles_[i]->fill(0.003);
            }

        }
    }
}

void TP3::renderScene()
{

    GLTexture::bind("chapa");
    GLTexture::unbind();
    glBegin(GL_QUADS);{
        glColor3f(1, 0, 0);
        glNormal3f(0,0,1);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-10, -10, 0);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(10,  -10, 0);

        glTexCoord2f(1.0, 1.0);
        glVertex3f( 10,  10, 0);

        glTexCoord2f(0.0, 1.0);
        glVertex3f( -10, 10, 0);

    }glEnd();

    for(int i=0; i<4; ++i)
        machines[i]->draw();

    belt_->draw();

    for(unsigned i=0; i<bottles_.size(); ++i)
        bottles_[i]->draw();
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
    switch(key){

    case 'x': xrot_ += 3; break;
    case 'X': xrot_ -= 3; break;

    case 'y': yrot_ += 3; break;
    case 'Y': yrot_ -= 3; break;

    case 'z': zrot_ += 3; break;
    case 'Z': zrot_ -= 3; break;

    case '-': ytrans_ -= 0.1; break;
    case '+': ytrans_ += 0.1; break;

    case 'r': xrot_ = yrot_ = zrot_ = 0; 
        ytrans_ = 0; break;

    case 's': stopAnimation = !stopAnimation; break;
        
    default: break;

    }
        
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

TP3::~TP3()
{
    delete belt_;

    for(unsigned i=0;i<bottles_.size();++i)
        delete bottles_[i];
    
    for(int i=0; i<4; ++i)
       	delete machines[i];

    delete dynamicsWorld_;
}

