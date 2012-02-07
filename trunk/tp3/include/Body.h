#ifndef _BODY_H_
#define _BODY_H_

#include "btBulletDynamicsCommon.h"
#include <GL/glew.h>
#include <GL/gl.h>

class Body
{
    protected:
    btRigidBody* rigidBody_;
    GLuint texture;

    public:
    Body();
    virtual void draw()=0;
    void setPosition(float x, float y, float z);
    btRigidBody* getRigidBody();
    btVector3 getPosition();
    void setTexture(GLuint t);

};

#endif /* _BODY_H_ */
