#ifndef __SUP_BARR_H_
#define __SUP_BARR_H_

#include "Primitive.h"
#include "btBulletDynamicsCommon.h"//cambiar esto

#define GRADO_BSPLINE 2

class SuperficieBarrido : public Primitive {

private:
	vectorPuntos ptosControl;
	vectorPuntos ptosPerfil;
	vectorPuntos normalesPerfil; //deberian ser uno solo
	matrizPuntos vertices;
	matrizPuntos normales;
	vectorPuntos ptosCurva;
	vectorPuntos tgsCurva;

	btVector3 calcularPuntoBSpline(float u, vectorPuntos ptosCtrl);
	btVector3 calcularTangenteBSpline(float u, vectorPuntos ptosCtrl);

	void cargarCoordenadas(unsigned pasosU);
	void cargarCoordenadasBSpline(unsigned pasosU);

public:
	SuperficieBarrido(vectorPuntos perfil, vectorPuntos normales, vectorPuntos ptosCtrl, unsigned pasosU = 10);
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

