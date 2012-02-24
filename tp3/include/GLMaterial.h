#ifndef _GLMATERIAL_H_
#define _GLMATERIAL_H_

#include <map>
#include <string>
#include <stack>

class GLMaterial
{

    static std::map<std::string, GLMaterial> materials_;
    static std::string currentMaterial_;
    static std::stack<std::string> stack;

    GLMaterial(float ka, float kd, float ks, float shininess);
    GLMaterial();

    float ka_, kd_, ks_, shininess_;

    public:
    static void create(std::string name, float ka, float kd, float ks, float shininess);
    static void use(std::string name);
    static std::string getCurrentMaterial();
    static void push(std::string name);
    static void pop();
};

#endif /* _GLMATERIAL_H_ */
