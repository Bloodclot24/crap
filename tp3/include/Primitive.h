#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

class Primitive
{
    public:
    Primitive();
    virtual void draw()=0;
    virtual ~Primitive();
};

#endif /* _PRIMITIVE_H_ */
