#include "Bodies/FillMachine.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLMaterial.h"


#include <GL/gl.h>

FillMachine::FillMachine(): cylinder_(0.82,0.4), sphere_(0.8)
{
	btVector3 patch0[4] = {btVector3(0.5,0.5,0),btVector3(-0.5,0.5,0),btVector3(-0.5,-0.5,0),btVector3(0.5,-0.5,0)};
	prism_.push_back(Prism(patch0, 4, 1));
	btVector3 patch1[4] = {btVector3(0.05,0,0.05),btVector3(-0.05,0,0.05),btVector3(-0.05,0,-0.05),btVector3(0.05,0,-0.05)};
	prism_.push_back(Prism(patch1, 4, 4));
	prism_.push_back(Prism(patch1, 4, 0.6));
	crearManguera();
	level = 0.2;
	subiendo = false;
}

void FillMachine::draw()
{

    glColor3f(0.1, 0.1, 0.1);

    glPushMatrix();{
    	glScalef(0.5, 0.5, 0.5);
    	glTranslatef(1.15,5.4,0.5);
    	prism_[0].draw();

    	glTranslatef(0,0,0.5);


        GLShader::pushProgram("cubic");
        GLTexture::bindCubic("cube1");
        GLShader::setUniform("cubeMap", (int)0);
        GLMaterial::push("steel");{

            GLShader::setUniform("mapZ", -0.4f);
            sphere_.draw();

            GLShader::setUniform("mapZ", -0.15f);
            cylinder_.draw();

            glTranslatef(0,0,0.4);
            GLShader::setUniform("mapZ", 0.25f);
            sphere_.draw();

            GLShader::setUniform("mapZ", 0);

            GLShader::popProgram();
        } GLMaterial::pop();

    	glTranslatef(0,0,level);
    	glPushMatrix();{
    		glTranslatef(0,0,0.8);
    		glScalef(0.4, 0.4, 0.8);
    		prism_[0].draw();
    	}glPopMatrix();
    	glTranslatef(0,-1.1,1);
    	glScalef(0.4,0.4,0.4);
    	glPushMatrix();{
    		glTranslatef(-0.3,0.65,-0.3);
    		prism_[1].draw();
    	}glPopMatrix();
    	glPushMatrix();{
    		glTranslatef(-0.3,0.65,0.3);
    		prism_[1].draw();
    	}glPopMatrix();
    	glPushMatrix();{
    		glTranslatef(0.3,0.65,-0.3);
    		prism_[1].draw();
    	}glPopMatrix();
    	glPushMatrix();{
    		glTranslatef(0.3,0.65,0.3);
    		prism_[1].draw();
    	}glPopMatrix();
    	glPushMatrix();{
    		glPushMatrix();{
    			glTranslatef(0,-1.3,0.3);
    			glRotatef(90,0,0,1);
    			prism_[2].draw();
    		}glPopMatrix();
    		glPushMatrix();{
    			glRotatef(90,0,1,0);
    			glTranslatef(0,-1.3,0.3);
    			glRotatef(90,0,0,1);
    			prism_[2].draw();
    		}glPopMatrix();
    		glPushMatrix();{
    			glRotatef(180,0,1,0);
    			glTranslatef(0,-1.3,0.3);
    			glRotatef(90,0,0,1);
    			prism_[2].draw();
    		}glPopMatrix();
    		glPushMatrix();{
    			glRotatef(-90,0,1,0);
    			glTranslatef(0,-1.3,0.3);
    			glRotatef(90,0,0,1);
    			prism_[2].draw();
    		}glPopMatrix();
    	}glPopMatrix();
    	glRotatef(-90,0,0,1);
    	glRotatef(90,1,0,0);
    	glColor3f(1, 1, 0);
    	manguera->draw();
    }glPopMatrix();

}

bool FillMachine::process(Bottle* bottle, float step) {
	if(level > 0 && !subiendo)
		level -= step;
	else if (!bottle->fill(step)) {
		level += step;
		subiendo = level < 0.2;
	}
	return level <= 0.2;
}

FillMachine::~FillMachine()
{
}

void FillMachine::crearManguera() {
	std::vector<btVector3> perfil, ptosControl;
	float radio = 0.3;
	int segmentos = 10;
    for (float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos)
    	perfil.push_back(btVector3(0, cos(i)*radio, sin(i)*radio));

	ptosControl.push_back(btVector3(-4, 0, 0));
	ptosControl.push_back(btVector3(-1, 0, 0));
	ptosControl.push_back(btVector3(1, 0, 0));
	ptosControl.push_back(btVector3(1, -2, 0));

    manguera = new SuperficieBarrido(perfil, perfil, ptosControl);
}
