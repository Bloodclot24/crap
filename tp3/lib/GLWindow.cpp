#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "GLWindow.h"

GLWindow* GLWindow::instance_ = NULL;

void GLWindow::displayStaticCallback()
{
    instance_->world_->handleDisplay();
}


void GLWindow::reshapeStaticCallback(int width, int height)
{
    instance_->world_->handleReshape(width, height);
}


void GLWindow::keyboardStaticCallback(unsigned char key, int x, int y)
{
    instance_->world_->handleKeyboard(key, x ,y);
}


void GLWindow::mouseClickStaticCallback(int button, int state, int x, int y)
{
    instance_->world_->handleMouseClick(button, state, x ,y);
}


void GLWindow::mouseMotionStaticCallback(int x, int y) 
{
    instance_->world_->handleMouseMotion(x, y);
}

void GLWindow::timerStaticCallback(int value)
{
    instance_->callTimerCallback(value);
}

void GLWindow::callTimerCallback(int value)
{
    world_->timerCallback(value);
    
    if(frameRate_ > 0)
        glutTimerFunc(1000/frameRate_, GLWindow::timerStaticCallback, 0);
}

GLWindow::GLWindow(GLWorld* world) 
{
    name_ = "GLUT";

    world_ = world;
    
    int argc = 1;
    char* argv[] = {(char*)"GLUT", (char*)NULL};

    frameRate_ = 0;

    glutInit(&argc, argv);
}


GLWindow* GLWindow::create(GLWorld* world, int width, int height, int flags) 
{

    assert(world != NULL);

    if(instance_ == NULL){
        instance_ = new GLWindow(world);
    } else {
        fprintf(stderr, "Only one GLWindow instance is allowed.\n");
        exit(-1);
    }

    glutInitDisplayMode(flags);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(instance_->name_.c_str());

    GLenum err = glewInit();
    if (GLEW_OK != err)	{
        fprintf(stderr,"Failed to initialize GLEW!\n");
        exit(-1);
    }

    printf("Using GLEW Version: %s\n", glewGetString(GLEW_VERSION));

    return instance_;
}

void GLWindow::setFrameRate(unsigned frameRate)
{
    frameRate_ = frameRate;
}

void GLWindow::show()
{
    glutDisplayFunc(displayStaticCallback);
    glutReshapeFunc(reshapeStaticCallback);
    glutKeyboardFunc(keyboardStaticCallback);
    glutMouseFunc(mouseClickStaticCallback);
    glutPassiveMotionFunc(mouseMotionStaticCallback);

    world_->initialize();

    if(frameRate_ != 0)
        glutTimerFunc(1000/frameRate_, timerStaticCallback, 0);

    glutMainLoop();
}
