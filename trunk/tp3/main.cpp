#include <stdlib.h>

#include "GLWindow.h"
#include "TP3.h"

int main(int argc, char *argv[])
{
        
    GLWorld* world = new TP3();

    GLWindow* window = GLWindow::create(world, 1280, 800);

    window->setFrameRate(30);

    window->show();

    return 0;
}
