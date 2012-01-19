#ifndef _BODY_H_
#define _BODY_H_

#include "btBulletDynamicsCommon.h"

class Body
{
    protected:
    btRigidBody* rigidBody_;

    public:
    Body();
    virtual void draw()=0;
    void setPosition(float x, float y, float z);
    btRigidBody* getRigidBody();
    btVector3 getPosition();

};

#endif /* _BODY_H_ */
