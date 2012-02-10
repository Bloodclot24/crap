#ifndef __SUP_BARR_H_
#define __SUP_BARR_H_

#include "Primitive.h"
#include "btBulletDynamicsCommon.h"//cambiar esto

#include "Curves/BSpline.h"

class SuperficieBarrido : public Primitive {

    private:
    vectorPuntos ptosPerfil;
    vectorPuntos normalesPerfil; //deberian ser uno solo
    matrizPuntos vertices;
    matrizPuntos normales;
    vectorPuntos ptosCurva;
    vectorPuntos tgsCurva;

    BSpline bspline_;

    void cargarCoordenadas();
    void cargarCoordenadasBSpline(unsigned pasosU);

    public:
    SuperficieBarrido(vectorPuntos perfil, vectorPuntos normales, BSpline bspline, unsigned pasosU = 10);
    ~SuperficieBarrido();
    void draw();
    matrizPuntos& getVertices(){
        return vertices;
    }
    matrizPuntos& getNormales(){
        return normales;
    }

};
#endif

