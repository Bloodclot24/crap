#ifndef __SUP_REV_H_
#define __SUP_REV_H_

#include "Primitive.h"
#include "btBulletDynamicsCommon.h"//cambiar esto

#include "Curves/Bezier.h"

#define GRADO_BEZIER 3

class SuperficieRevolucion : public Primitive {

    private:
    vectorPuntos ptosControl;
    matrizPuntos vertices;
    matrizPuntos normales;
    Bezier bezier_;

    vectorPuntos discretizarBezier(unsigned pasosT);
    void cargarNormales();
    void drawPrimitive();


public:

    SuperficieRevolucion(Bezier perfil, unsigned rotaciones=10, 
                         unsigned pasosT=100, unsigned grados=360, 
                         btVector3 axis=btVector3(0,0,1));

    ~SuperficieRevolucion();
    matrizPuntos& getVertices(){
        return vertices;
    }
    matrizPuntos& getNormales(){
        return normales;
    }

};
#endif

