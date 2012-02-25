#ifndef _TP3_H_
#define _TP3_H_

#include "btBulletDynamicsCommon.h"
#include <vector>

#include "GLWorld.h"
#include "Body.h"
#include "Bodies/Bottle.h"
#include "Bodies/CoveyorBelt2.h"
#include "Bodies/Machine.h"
#include "Bodies/Pack.h"
#include "Curves/Bezier.h"

#define SPEED 4

class TP3 : public GLWorld
{
    private:

    int windowWidth_,
        windowHeight_;

    Bezier bottleCurve_;

    std::vector<Bottle*> bottles_;
    std::vector<float> bottlesPositions_;
    std::vector<Pack> packs_;

    float bottleInterval_;
    float nextBottle_;
    unsigned firstBottle_;
    bool processing1_;
    bool processing2_;
    int processingBottle_;

    Machine* machines[4];
    CoveyorBelt* belt_;

    float xrot_, yrot_, zrot_;
    float xtrans_, ytrans_, ztrans_;
    int x_mouse;
    int y_mouse;
    float angle;
    float xlookat_;
    float ylookat_;
    float zlookat_;

    bool stopAnimation;

    bool compiledLists;
    bool spectator;

    btDiscreteDynamicsWorld* dynamicsWorld_;

    void initializePhysics();

    void setUpGlContext();

    void updateScene();

    void renderScene();

    void addBody(Body* body);

    void updateBottlesPositions();

    void processBottles();

    void reset();

    public:

    virtual void initialize();
    virtual void handleDisplay();
    virtual void handleReshape(int width, int height);
    virtual void handleKeyboard(unsigned char key, int x, int y);
    virtual void timerCallback(int value);
    virtual void handleMouseMotion(int x, int y);

    TP3();
    virtual ~TP3();
};

#endif /* _TP3_H_ */
