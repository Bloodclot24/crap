#ifndef _TP3_H_
#define _TP3_H_

#include "btBulletDynamicsCommon.h"
#include <vector>

#include "GLWorld.h"
#include "Body.h"
#include "Bodies/Bottle.h"
#include "Bodies/CoveyorBelt2.h"
#include "Bodies/Machine.h"

class TP3 : public GLWorld
{
    private:

    int windowWidth_,
        windowHeight_;

    std::vector<Bottle*> bottles_;
    std::vector<float> bottlesPositions_;

    float bottleInterval_;
    float nextBottle_;
    int firstBottle_;

    Machine* machines[4];
    CoveyorBelt* belt_;

    float xrot_, yrot_, zrot_;
    float xtrans_, ytrans_, ztrans_;

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
    virtual ~TP3();
};

#endif /* _TP3_H_ */
