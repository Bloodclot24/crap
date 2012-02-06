#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <string>

class Vertex
{
    private:
    float x_, y_, z_;

    public:
    Vertex();
    Vertex(float x, float y, float z);

    std::string toString();

    void setCoords(float x, float y,float z);

    float getX();
    float getY();
    float getZ();

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    Vertex operator-(Vertex v);
    Vertex operator-();
    Vertex operator+(Vertex v);
    Vertex operator*(float t);
    Vertex crossProduct(Vertex v);

    float  abs();
    Vertex normalize();
};

#endif /* _VERTEX_H_ */
