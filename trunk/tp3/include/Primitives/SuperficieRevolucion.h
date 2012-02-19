#ifndef __SUP_REV_H_
#define __SUP_REV_H_

#include "Primitive.h"
#include "btBulletDynamicsCommon.h"//cambiar esto

#define GRADO_BEZIER 3

class SuperficieRevolucion : public Primitive {

private:
	vectorPuntos ptosControl;
	matrizPuntos vertices;
	matrizPuntos normales;

	btVector3 calcularPuntoBezier(float u, vectorPuntos perfil);

	void cargarCoordenadasBezier(unsigned pasosU);
	void cargarNormales();
	int factorial(int n);
	void drawPrimitive();


public:

	SuperficieRevolucion(vectorPuntos perfil, unsigned rotaciones = 10,
			unsigned pasosPerfil = 10, unsigned grados = 360, btVector3 axis = btVector3(0,0,1));
	~SuperficieRevolucion();
	matrizPuntos& getVertices(){
		return vertices;
	}
	matrizPuntos& getNormales(){
		return normales;
	}

};
#endif

