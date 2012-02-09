#include "Primitives/SuperficieBarrido.h"
#include <GL/glu.h>

SuperficieBarrido::SuperficieBarrido(vectorPuntos perfil, vectorPuntos normales, vectorPuntos ptosCtrl,
		unsigned pasosU) : ptosControl(ptosCtrl), ptosPerfil(perfil), normalesPerfil(normales) {

	cargarCoordenadas(pasosU);
}

SuperficieBarrido::~SuperficieBarrido() {
}

void SuperficieBarrido::cargarCoordenadas(unsigned pasosU) {
	cargarCoordenadasBSpline(pasosU);
	btVector3 axisZ(0,0,1);
	btVector3 axisX(1,0,0);
	std::vector<btVector3> ptos(ptosPerfil.size()), normal(ptosPerfil.size());
	for (unsigned i = 0; i < ptosCurva.size(); i++) {
		for (unsigned j = 0; j < ptosPerfil.size(); j++) {
			if(tgsCurva[i][1] < 0) {
				ptos[j] = ptosPerfil[j].rotate(axisZ, - tgsCurva[i].angle(axisX)) + ptosCurva[i];
				normal[j] = normalesPerfil[j].rotate(axisZ, - tgsCurva[i].angle(axisX));
			} else {
				ptos[j] = ptosPerfil[j].rotate(axisZ, tgsCurva[i].angle(axisX)) + ptosCurva[i];
				normal[j] = normalesPerfil[j].rotate(axisZ, tgsCurva[i].angle(axisX));
			}
		}
		vertices.push_back(ptos);
		normales.push_back(normal);
	}
}

void SuperficieBarrido::cargarCoordenadasBSpline(unsigned pasosU) {
	std::vector<btVector3> ptosCtrlCurva;
	for (unsigned offset = 0; offset < ptosControl.size() - GRADO_BSPLINE; offset++) {
		ptosCtrlCurva.clear();
		for (int i = 0; i < GRADO_BSPLINE + 1; i++)
			ptosCtrlCurva.push_back(ptosControl[offset + i]);
		for (float u = 0; u < 1; u += 1 / (float) pasosU) { //u=1 es igual a u=0 en siguiente curva
			ptosCurva.push_back(calcularPuntoBSpline(u, ptosCtrlCurva));
			tgsCurva.push_back(calcularTangenteBSpline(u, ptosCtrlCurva));
		}
	}
	ptosCurva.push_back(calcularPuntoBSpline(1, ptosCtrlCurva));
	tgsCurva.push_back(calcularTangenteBSpline(1, ptosCtrlCurva));
}

btVector3 SuperficieBarrido::calcularPuntoBSpline(float u, vectorPuntos ctrlPts) {
	float b0 = 0.5 * (1 - u) * (1 - u);
	float b1 = 0.5 * (1 + u) * (1 - u) + 0.5 * u * (2 - u);
	float b2 = 0.5 * u * u;
	return b0 * ctrlPts[0] + b1 * ctrlPts[1] + b2 * ctrlPts[2];
}

btVector3 SuperficieBarrido::calcularTangenteBSpline(float u, vectorPuntos ctrlPts) {
	float tgb0 = u - 1;
	float tgb1 = 1 - 2 * u;
	float tgb2 = u;
	return tgb0 * ctrlPts[0] + tgb1 * ctrlPts[1] + tgb2	* ctrlPts[2];
}

void SuperficieBarrido::draw() {
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned i = 0; i < vertices.size() - 1 ; i++) {
		for (unsigned j = 0; j < vertices[i].size(); j++) {
			glNormal3fv(normales[i][j]);
			glVertex3fv(vertices[i][j]);
			glNormal3fv(normales[i + 1][j]);
			glVertex3fv(vertices[i + 1][j]);
		}
	}
	glEnd();

}
