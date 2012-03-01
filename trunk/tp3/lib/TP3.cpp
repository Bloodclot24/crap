#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GLShader.h"
#include "GLTexture.h"
#include "GLMaterial.h"

#include "Primitives/Cube.h"
#include "Primitives/Cylinder.h"
#include "Bodies/FirstMachine.h"
#include "Bodies/LastMachine.h"
#include "Bodies/LabelMachine.h"
#include "Bodies/FillMachine.h"
#include "TP3.h"
#include "GlobalParameters.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

btVector3 la(0,0,0);
int valores[] = {0, 1, -1};


GLfloat position0[] = { 9.8, 9.8, 10, 1.0 };
GLfloat position1[] = { -9.8, -9.8, 10, 1.0};
GLfloat position2[] = { 7, -4, 10, 1.0};
GLfloat position3[] = { 3.0f, 0.0f, 10.0f, 1.0f };
GLfloat position4[] = { -3.0f, 0.0f, 10.0f, 1.0f };
GLfloat position5[] = { 0.0f, 0.0f, 10.0f, 1.0f };

TP3::TP3()
{
    windowWidth_ = 1;
    windowHeight_ = 1;
    dynamicsWorld_ = NULL;

    vectorPuntos controlPoints;
    for(int i=0;!isnan(beltControlPoints[i][0]);i++){
        controlPoints.push_back(btVector3(beltControlPoints[i][0],
                                          beltControlPoints[i][1],
                                          beltControlPoints[i][2]));
    }

    BSpline curve(controlPoints);

    belt_ = new CoveyorBelt(curve);

    controlPoints.clear();
    for(int i=0;!isnan(bottleControlPoints[i][0]);i++){
        controlPoints.push_back(btVector3(bottleControlPoints[i][0],
                                          bottleControlPoints[i][1],
                                          bottleControlPoints[i][2]));
    }

    Bezier bezierCurve(controlPoints);
    bottleCurve_ = bezierCurve;
    

    bottleInterval_ = 27.0*5.0/SPEED;
    nextBottle_ = 0;
    firstBottle_ = 0;
    processingBottle_ = -1;
    processing1_ = false;
    processing2_ = false;

    machines[0] = new FirstMachine();
    machines[1] = new LabelMachine();
    machines[2] = new FillMachine();
    machines[3] = new LastMachine();

    reset();

    stopAnimation = false;
    spectator = false;
    packs_.push_back(Pack());

    compiledLists = false;

}

void TP3::reset()
{
    xrot_ = yrot_ = zrot_ = 0;

    trans_[0] = 0;
    trans_[1] = -8;
    trans_[2] = 1;
    x_mouse = 0;
    y_mouse = 0;
    angle = 0;
}

void TP3::initialize()
{
    initializePhysics();

    addBody(machines[3]);

    //Cargo texturas
    GLTexture::load("lad.raw", "ladrillos");
    GLTexture::load("16metal.raw", "chapa");
    GLTexture::load("cintita.raw", "cinta");
    GLTexture::load("eti.raw", "etiqueta");
    GLTexture::createCube("cube1");
    GLTexture::load("t.raw", "piso");
    GLTexture::load("Metal.raw", "techo");

    //Cargo VShaders
    GLShader::loadVShader("shaders/light.vert", "light");
    GLShader::loadVShader("shaders/cubic.vert", "cubic");

    //Cargo FShaders
    GLShader::loadFShader("shaders/base.frag", "base");
    GLShader::loadFShader("shaders/texture.frag", "texture");
    GLShader::loadFShader("shaders/light.frag", "light");
    GLShader::loadFShader("shaders/belt.frag", "belt");
    GLShader::loadFShader("shaders/bottle.frag", "bottle");
    GLShader::loadFShader("shaders/cubic.frag", "cubic");
    GLShader::loadFShader("shaders/noTexture.frag", "noTexture");

    //Creo los programas
    const char* lightVShader[]  = {"light", NULL};
    const char* cubicVShader[]  = {"cubic", NULL};

    const char* normalFShader[]  = {"base", "texture",  "light", NULL};
    const char* beltFShader[]    = {"base", "belt",     "light", NULL};
    const char* bottleFShader[]  = {"base", "bottle",   "light", NULL};
    const char* reflectFShader[] = {"base", "cubic", "light", NULL}; 

    GLShader::createProgram("normal", lightVShader, normalFShader);
    GLShader::createProgram("belt",   lightVShader, beltFShader);
    GLShader::createProgram("bottle", lightVShader, bottleFShader);
    GLShader::createProgram("cubic",  cubicVShader, reflectFShader);
    

    GLMaterial::create("matte", 0.2, 0.5, 0.8, 100);
    GLMaterial::create("glass", 0.2, 0.4, 3, 10);
    GLMaterial::create("steel", 0.2, 0.4, 10, 10);

    GLShader::pushProgram("normal");
    GLMaterial::push("matte");

    //Activo iluminacion
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);

    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular2[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT5, GL_SPECULAR, specular);

    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);

    GLfloat diffuse[] = { 1, 1, 1, 1};
    GLfloat diffuse2[] = { 1, 1, 1, 1};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);

    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightfv(GL_LIGHT3, GL_POSITION, position3);
    glLightfv(GL_LIGHT4, GL_POSITION, position4);
    glLightfv(GL_LIGHT5, GL_POSITION, position5);

    GLfloat spot_direction0[] = { -0.5, -0.5, -1.0 };
    GLfloat spot_direction1[] = { 0.5, 0.5, -1.0 };
    GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction0);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_direction);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);
}

void TP3::setUpGlContext()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective( 45.0, 
                    (GLfloat)windowWidth_/(GLfloat)windowHeight_, 
                    0.10, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(spectator) {

    	btVector3 newLookAt = btVector3(0,6,1).rotate(btVector3(0,0,1), angle) + trans_;
        gluLookAt(trans_[0], trans_[1], trans_[2],
                  newLookAt[0], newLookAt[1], newLookAt[2],
                  0,  0, 1);

    } else {

        gluLookAt(trans_[0], trans_[1], trans_[2],
                  0, 0, 0,
                  0, 0, 1);

        glRotatef(xrot_, 1, 0, 0);
        glRotatef(yrot_, 0, 1, 0);
        glRotatef(zrot_, 0, 0, 1);
    }

    float matriz_vista[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matriz_vista);

    GLShader::setUniformM("matriz_vista", matriz_vista);
    GLShader::pushProgram("belt");
    GLShader::setUniformM("matriz_vista", matriz_vista);
    GLShader::popProgram();
    GLShader::pushProgram("bottle");
    GLShader::setUniformM("matriz_vista", matriz_vista);
    GLShader::popProgram();
    GLShader::pushProgram("cubic");
    GLShader::setUniformM("matriz_vista", matriz_vista);
    GLShader::popProgram();
}

void TP3::updateScene()
{
    if (!stopAnimation) {
        dynamicsWorld_->stepSimulation(1.0 / 30.0, 10);
        if (!processing1_ && !processing2_) {

            belt_->advance(0.01 * 2 * SPEED);

            nextBottle_ -= 1.0;
            if (nextBottle_ <= 0) {
                nextBottle_ = bottleInterval_;
                bottles_.push_back(new Bottle(bottleCurve_));
                bottlesPositions_.push_back(0);
            }

            updateBottlesPositions();

        } else
            processBottles();
    }
}

void TP3::updateBottlesPositions() {
    for (unsigned i = firstBottle_; i < bottles_.size(); i++) {
        btVector3 pos = belt_->getPosition(bottlesPositions_[i]);
        btVector3 tangent = belt_->getTangent(bottlesPositions_[i]);
        bottlesPositions_[i] += 0.001 * SPEED;

        if (bottlesPositions_[i] >= 1) {
            firstBottle_ = i + 1;
            if(packs_[packs_.size() - 1].getBottlesCount() >= 4) {
                packs_[packs_.size() - 1].setPosition(5, 2.4, 1.6);
                addBody(&packs_[packs_.size() - 1]);
                packs_.push_back(Pack());
            }
            packs_[packs_.size() - 1].addBottle(bottles_[i]);

        } else if (bottlesPositions_[i] >= 0.617 && bottlesPositions_[i] <= 0.617 + 0.001 * SPEED) {
            processing1_ = true;
            if (i != firstBottle_)
                processing2_ = true;
            processingBottle_ = i;

        } else {
            bottles_[i]->setPosition(pos.x(), pos.y(), pos.z() + 0.265);
            bottles_[i]->setRotation(0, 0, acos(
                                                tangent.normalize().dot(btVector3(1, 0, 0))));
        }
    }
}

void TP3::processBottles() {
    if (processing1_)
        processing1_ = machines[1]->process(
                                            bottles_[processingBottle_], 0.002 * SPEED);
    if (processing2_)
        processing2_ = machines[2]->process(bottles_[processingBottle_
                                                     - 1], 0.004 * SPEED);
}

void TP3::renderScene()
{

    GLTexture::bind("piso");

    glBegin(GL_QUADS);{
        glColor3f(0.5, 0.5, 0.2);
        glNormal3f(0,0,1);

        for (int i = -10; i < 10; i++)
            for (int j = -10; j < 10; j++) {
                glTexCoord2f(0.0, 0.0);
                glVertex3f(i, j, 0);

                glTexCoord2f(1.0, 0.0);
                glVertex3f(i+1,  j, 0);

                glTexCoord2f(1.0, 1.0);
                glVertex3f( i+1,  j+1, 0);

                glTexCoord2f(0.0, 1.0);
                glVertex3f( i, j+1, 0);
            }

    }glEnd();

    GLTexture::bind("techo");

    glBegin(GL_QUADS);{
        glColor3f(0.5, 0.5, 0.2);
        glNormal3f(0,0,-1);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-10, -10, 10);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(10, -10, 10);

        glTexCoord2f(1.0, 1.0);
        glVertex3f( 10, 10, 10);

        glTexCoord2f(0.0, 1.0);
        glVertex3f( -10, 10, 10);
    }glEnd();

    GLTexture::bind("ladrillos");
    glBegin(GL_QUADS);{
        glColor3f(1, 1, 1);
        for (int i = 0; i < 10; i++) {
            glNormal3f(0, -1, 0);
            for (int j = -10; j < 10; j++) {
                glTexCoord2f(0.0, 0.0);
                glVertex3f(j, 10, i);

                glTexCoord2f(1.0, 0.0);
                glVertex3f(j + 1, 10, i);

                glTexCoord2f(1.0, 1.0);
                glVertex3f(j + 1, 10, i + 1);

                glTexCoord2f(0.0, 1.0);
                glVertex3f(j, 10, i + 1);
            }
            glNormal3f(0, 1, 0);
            for (int j = -10; j < 10; j++) {
                glTexCoord2f(0.0, 0.0);
                glVertex3f(j + 1, -10, i);

                glTexCoord2f(1.0, 0.0);
                glVertex3f(j, -10, i);

                glTexCoord2f(1.0, 1.0);
                glVertex3f(j, -10, i + 1);

                glTexCoord2f(0.0, 1.0);
                glVertex3f(j + 1, -10, i + 1);
            }
            glNormal3f(1, 0, 0);
            for (int j = -10; j < 10; j++) {
                glTexCoord2f(0.0, 0.0);
                glVertex3f(-10, j, i);

                glTexCoord2f(1.0, 0.0);
                glVertex3f(-10, j + 1, i);

                glTexCoord2f(1.0, 1.0);
                glVertex3f(-10, j + 1, i + 1);

                glTexCoord2f(0.0, 1.0);
                glVertex3f(-10, j, i + 1);
            }
            glNormal3f(-1, 0, 0);
            for (int j = -10; j < 10; j++) {
                glTexCoord2f(0.0, 0.0);
                glVertex3f(10, j + 1, i);

                glTexCoord2f(1.0, 0.0);
                glVertex3f(10, j, i);

                glTexCoord2f(1.0, 1.0);
                glVertex3f(10, j, i + 1);

                glTexCoord2f(0.0, 1.0);
                glVertex3f(10, j + 1, i + 1);
            }
        }
    }glEnd();

    for(int i=0; i<4; ++i)
        machines[i]->draw();
    
    belt_->draw();

    for(unsigned i=0; i<packs_.size() - 1; ++i)
        packs_[i].draw();

    for(unsigned i=firstBottle_; i<bottles_.size(); ++i)
        bottles_[i]->draw();


}

void TP3::setUpCubeContext(int face)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90, 1,
                   0.75, 50.0);
    
    if(face == 4){
        glClearColor(0,0,0,1);
    }
    else{
        glClearColor(0.2,0.2,0.2,1);
    }

    glClearDepth(30.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float 
        x = 1.15/2,
        y = 5.4/2,
        z = 0.5/2;

    float faces[][3] = {{ 1, 0, 0},
                        {-1, 0, 0},
                        { 0, 1, 0},
                        { 0,-1, 0},
                        { 0, 0, 1},
                        { 0, 0,-1}};

    float up[][3] = {{0,-1, 0},
                     {0,-1, 0},
                     {0, 0, 1},
                     {0, 0,-1},
                     {0,-1, 0},
                     {0,-1, 0}};

    glLoadIdentity();

    float matriz_camara[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matriz_camara);

    if(face == 5){
        x=0;
        y=0;
        z = 1;
    }

    gluLookAt(x, y, z,
              x + faces[face][0], y + faces[face][1], z + faces[face][2],
              up[face][0], up[face][1], up[face][2]);
}


void TP3::renderCube()
{
    static GLuint framebuffer=0, depthbuffer=0;

    if(framebuffer == 0){
        glGenFramebuffers(1, &framebuffer);
        glGenFramebuffers(1, &depthbuffer);
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
    for(int i=0;i<6;i++){
        GLTexture::beginRenderToCube("cube1", i);
        GLTexture::bindCubic("cube1");

        setUpCubeContext(i);

        glViewport(0, 0, 512, 512);
        renderScene();
    }

    glViewport(0,0,windowWidth_, windowHeight_);

    GLTexture::endRenderToCube();

    setUpGlContext();

    glColor3f(1,1,1);

    // glTranslatef(5,-5,1);
    // GLShader::pushProgram("cubic");
    // GLTexture::bindCubic("cube1");
    // GLShader::setUniform("cubeMap", (int)0);
    // //Cube c(1);
    // Sphere s(1);
    //  s.draw();
    // //c.draw();
    // GLShader::popProgram();
}

void TP3::handleDisplay()
{
    setUpGlContext();

    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateScene();

    renderScene();

    renderCube();

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

    case 'e': spectator = ! spectator;
        if(!spectator)
            glutSetCursor(GLUT_CURSOR_INHERIT);
        else
            glutSetCursor(GLUT_CURSOR_NONE);
    case 'r': reset(); break;

    case 'S': stopAnimation = !stopAnimation; break;

    case 'c': compiledLists = !compiledLists; 
        Primitive::useCompiledLists(compiledLists); break;
        
    case 'q': exit(0); break;

    default: break;
    }

    if(spectator) {
        switch(key){

        case 'a': trans_ += btVector3(-0.1,0,0).rotate(btVector3(0,0,1), angle); break;

        case 'd': trans_ += btVector3(0.1,0,0).rotate(btVector3(0,0,1), angle); break;

        case 's': trans_ += btVector3(0,-0.1,0).rotate(btVector3(0,0,1), angle); break;

        case 'w': trans_ += btVector3(0,0.1,0).rotate(btVector3(0,0,1), angle); break;

        default: break;
        }
    } else {
        switch(key){

        case 'x': xrot_ += 3; break;
        case 'X': xrot_ -= 3; break;

        case 'y': yrot_ += 3; break;
        case 'Y': yrot_ -= 3; break;

        case 'z': zrot_ += 3; break;
        case 'Z': zrot_ -= 3; break;

        case '-': trans_[1] -= 0.1; break;
        case '+': trans_[1] += 0.1; break;

        case 'i': la[0] = valores[int(la[0])+1]; break;
        case 'o': la[1] = valores[int(la[1])+1]; break;
        case 'p': la[2] = valores[int(la[2])+1]; break;

        default: break;

        }
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

    groundRigidBody->setFriction(0.3);

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

void TP3::handleMouseMotion(int x, int y)
{
    if(spectator) {
        if (x_mouse < x)
            angle -= 0.05;
        else if(x_mouse > x)
            angle += 0.05;
        x_mouse = x;

        if (x_mouse < windowWidth_ / 20 || x_mouse > 19 * windowWidth_ / 20) {
            x_mouse = windowWidth_ / 2;
            glutWarpPointer(x_mouse, windowHeight_ / 2);
        }
        if(y_mouse < windowHeight_ / 20 || y_mouse > 19* windowHeight_ / 20){
            y_mouse = windowHeight_ / 2;
            glutWarpPointer(x_mouse, y_mouse);
        }
    }
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

