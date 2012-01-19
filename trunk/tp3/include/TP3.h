#ifndef _TP3_H_
#define _TP3_H_

#include "btBulletDynamicsCommon.h"

#include "GLWorld.h"
#include "Body.h"
#include "Bodies/Bottle.h"

class TP3 : public GLWorld
{
    private:

    int windowWidth_,
        windowHeight_;

    Bottle bottles[5];

    btDiscreteDynamicsWorld* dynamicsWorld_;

    void initializePhysics();

    void setUpGlContext();

    void updateScene();

    void renderScene();

    void addBody(Body* body);

    public:

    virtual void initialize();
    virtual void handleDisplay();
    virtual void handleReshape(int width, int height);
    virtual void handleKeyboard(unsigned char key, int x, int y);
    virtual void timerCallback(int value);

    TP3();
};

#endif /* _TP3_H_ */
