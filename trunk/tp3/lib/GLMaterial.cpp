#include "GLMaterial.h"
#include "GLShader.h"

std::map<std::string, GLMaterial> GLMaterial::materials_;
std::string GLMaterial::currentMaterial_;
std::stack<std::string> GLMaterial::stack;

GLMaterial::GLMaterial(float ka, float kd, float ks, float shininess)
{
    ka_ = ka;
    kd_ = kd;
    ks_ = ks;
    shininess_ = shininess;
}

GLMaterial::GLMaterial()
{
    ka_ = 0;
    kd_ = 0;
    ks_ = 0;
    shininess_ = 0;
}

void GLMaterial::create(std::string name, float ka, float kd, float ks, float shininess)
{
    GLMaterial material(ka, kd, ks, shininess);
    materials_.insert(std::pair<std::string, GLMaterial>(name, material));
}

void GLMaterial::use(std::string name)
{
    currentMaterial_ = name;

    if(materials_.find(name) != materials_.end()){
        GLMaterial material = materials_.at(name);

        GLShader::setUniform("ka", material.ka_);
        GLShader::setUniform("kd", material.kd_);
        GLShader::setUniform("ks", material.ks_);
        GLShader::setUniform("shininess", material.shininess_);
    }
}

std::string GLMaterial::getCurrentMaterial()
{
    return currentMaterial_;
}

void GLMaterial::push(std::string name)
{
    stack.push(name);
    use(name);
}

void GLMaterial::pop()
{
    stack.pop();
    use(stack.top());
}
