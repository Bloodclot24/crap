#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_

#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GL/glut.h>

#include "GLWorld.h"


class GLWindow
{
    private:

    std::string name_;

    GLWorld* world_;

    unsigned frameRate_;

    static GLWindow* instance_;

    GLWindow(GLWorld* world);

    static void displayStaticCallback();
    static void reshapeStaticCallback(int width, int height);
    static void keyboardStaticCallback(unsigned char key, int x, int y);
    static void mouseClickStaticCallback(int button, int state, int x, int y);
    static void mouseMotionStaticCallback(int x, int y);
    static void timerStaticCallback(int value);

    void callTimerCallback(int value);
    public:

    static GLWindow* create(GLWorld* world, int width=1024, int height=768, int flags=GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    void setFrameRate(unsigned frameRate);
    
    void show();
};


#endif /* _GLWINDOW_H_ */
