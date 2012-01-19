// BulletHolaMundo.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "btBulletDynamicsCommon.h"


#include <GL/glut.h>
#include <math.h>

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)
#define DL_AXIS2D_HEIGHT (dl_handle+3)

// Tamaño de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

// Variables asociadas a la fuente de luz de la escena
float light_color[4] = {2.0f,2.0f, 2.0f, 1.0f};
float light_color2[4] = {0.3f, 0.3f, 2.0f, 1.0f};
float light_ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};

GLfloat colorEsfera[3]={0.0,0.5,1.0};
btRigidBody* esferaRB;
btDiscreteDynamicsWorld* dynamicsWorld;

void DrawAxis()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);{
	// X
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(15.0, 0.0, 0.0);
	// Y
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 15.0, 0.0);
	// Z
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 15.0);
    }glEnd();
    glEnable(GL_LIGHTING);
	
}

void DrawXYGrid()
{
    int i;
    glDisable(GL_LIGHTING);
    glColor3f(0.15, 0.1, 0.1);
    glBegin(GL_LINES);
    for(i=-20; i<21; i++)
	{
	    glVertex3f(i, -20.0, 0.0);
	    glVertex3f(i,  20.0, 0.0);
	    glVertex3f(-20.0, i, 0.0);
	    glVertex3f( 20.0, i, 0.0);
	}
    glEnd();
    glEnable(GL_LIGHTING);
}

void setMaterial(GLfloat diffuseColor[3]){

    GLfloat ambientColor[] = {0.1, 0.1, 0.1}; 
    GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
    GLfloat mShininess[] = {128};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
    
}


void Set3DEnv()
{
    glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 600.0);
}

void drawCube(GLfloat color[3], GLfloat ladoY,GLfloat ladoX,GLfloat ladoZ){
    glEnable(GL_LIGHTING);
    // crea un cubo con base en el plano XY y centrado en 0,0,0 de ladoX * ladoY * lado Z

    setMaterial(color);

    glPushMatrix();
    glTranslatef(0,0,0); 
    glScalef(ladoX,ladoY,ladoZ);
    glutSolidCube(1);
    glPopMatrix();


}

void init(void) 
{
    dl_handle = glGenLists(3);

    glClearColor (0.02, 0.02, 0.04, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    float pos[3]={150.0f, 150.0f, 50.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);    
    glLightfv(GL_LIGHT0, GL_POSITION,pos);  
    glEnable(GL_LIGHT0);

    float pos2[3]={-150.0f, 150.0f, 50.0f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE,light_color2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);   
    glLightfv(GL_LIGHT1, GL_POSITION, pos2);  
    glEnable(GL_LIGHT1);

    glEnable(GL_LIGHTING);


    // Generación de las Display Lists
    glNewList(DL_AXIS, GL_COMPILE);{
	DrawAxis();
    }glEndList();
    
    glNewList(DL_GRID, GL_COMPILE);{
	DrawXYGrid();
    }glEndList();

}

void displayEscena(void){

    // Dibujo La esfera
    glPushMatrix();{
	setMaterial(colorEsfera);

	btTransform trans;
	esferaRB->getMotionState()->getWorldTransform(trans); 

	btVector3 pos=trans.getOrigin();
	glTranslatef(pos.getX(),pos.getY(),pos.getZ());// unico centro de masa 

	btVector3 axis=trans.getRotation().getAxis(); // aplico orientacion
	glRotatef(trans.getRotation().getAngle()*360/6.2832f,axis.getX(),axis.getY(),axis.getZ());

	glutSolidSphere(1,16,16);			

    }glPopMatrix();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///////////////////////////////////////////////////
    // Escena 3D
    Set3DEnv();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    gluLookAt (10,10,10,0,0,0,0,0,1);
   
    glCallList(DL_AXIS);// ejes
    glCallList(DL_GRID);// grilla

    displayEscena();

    glutSwapBuffers();
}


void reshape (int w, int h)
{
    W_WIDTH  = w;
    W_HEIGHT = h;
}

void OnIdle (void){
    dynamicsWorld->stepSimulation(1/60.f,10);
    glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
    case 0x1b:
	exit (0);
	break;

    default:
	break;
    }
}



void initPhysics()
{
    // Inicializacion del motor de fisica
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
 
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
 
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,0,-10));
 
    // Definimos plano del suelo - Cuerpo rigido estatico (masa=0)
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,0,1),1);// parametros: normal {x,y,z} , espesor o altura
     
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,-1))); 
    //los 2 vectores representan la orientacion (x,y,z,w) y traslacion (x,y,z) del objeto suelo,
    // traslacion es (0,-1,0) para compensar el espesor que es 1, asi el lado superior del piso queda en Y=0

    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    groundRigidBody->setRestitution(1.0);
    groundRigidBody->setFriction(1.0);
    dynamicsWorld->addRigidBody(groundRigidBody);

    btScalar mass = 1;
    btVector3 fallInertia(0,0,0);

    // Defino Esfera

    btCollisionShape* esferaShape = new  btSphereShape(btScalar(1));
    mass = 100;
    esferaShape->calculateLocalInertia(mass,fallInertia);
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(btScalar(0),btScalar(0),btScalar(20)));
    btDefaultMotionState* esferaMotionState = new btDefaultMotionState(startTransform);

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI2(mass,esferaMotionState,esferaShape,fallInertia);
    esferaRB = new btRigidBody(fallRigidBodyCI2);

    esferaRB->setRestitution(btScalar(0.6));
    esferaRB->setFriction(btScalar(0.0));
    //esferaRB->setCollisionFlags( esferaRB->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    //esferaRB->setActivationState(DISABLE_DEACTIVATION);

    dynamicsWorld->addRigidBody(esferaRB);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1024, 768); 
    glutInitWindowPosition (0, 0);
    glutCreateWindow (argv[0]);   
    init ();
    initPhysics();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(OnIdle);
    glutMainLoop();
}

