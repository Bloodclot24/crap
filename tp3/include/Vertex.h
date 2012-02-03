#ifndef _VERTEX_H_
#define _VERTEX_H_

class Vertex
{
    private:
    float x_, y_, z_;

    public:
    Vertex();
    void setCoords(float x, float y,float z);

    float getX();
    float getY();
    float getZ();

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    Vertex operator-(Vertex v);
    Vertex operator+(Vertex v);
    Vertex operator*(float t);

    float  abs();
    Vertex normalize();
};

#endif /* _VERTEX_H_ */
