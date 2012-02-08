#include "Primitives/SuperficieRevolucion.h"
#include <GL/glu.h>

SuperficieRevolucion::SuperficieRevolucion(vectorPuntos perfil,
		unsigned rotaciones, unsigned pasosU, unsigned grados, btVector3 axis) : ptosControl(perfil) {
	for (unsigned i = 0; i < rotaciones; i++) {
		cargarCoordenadasBezier(pasosU);
		for (unsigned j = 0; j < ptosControl.size(); j++)
			ptosControl[j] = ptosControl[j].rotate(axis, 2*M_PI / rotaciones);
	}
	cargarNormales();
}

SuperficieRevolucion::~SuperficieRevolucion() {
}

void SuperficieRevolucion::cargarNormales() {
	btVector3 x, y;
	for(unsigned i = 0; i < vertices.size(); i++) {
		normales.push_back(std::vector<btVector3>());
		for(unsigned j = 0; j < vertices[i].size() - 1; j++) {
			x = vertices[fmod(i + 1, vertices.size())][j] - vertices[i][j];
			y =  vertices[i][j+1] - vertices[i][j];
			normales[i].push_back(x.cross(y));
		}
		//Calculo de ultima normal
		y = vertices[fmod(i + 1, vertices.size())][vertices.size()] - vertices[i][vertices.size()];
		x =  vertices[i][vertices.size()-1] - vertices[i][vertices.size()];
		normales[i].push_back(x.cross(y));
	}
}

void SuperficieRevolucion::cargarCoordenadasBezier(unsigned pasosU) {
	std::vector<btVector3> ptos, perfil;
	for (unsigned offset = 0; offset < ptosControl.size() - GRADO_BEZIER; offset
			+= GRADO_BEZIER) {//ignora los ptos de control q sobran
		perfil.clear();
		for (int i = 0; i < GRADO_BEZIER + 1; i++)
			perfil.push_back(ptosControl[offset + i]);
		for (float u = 0; u < 1; u += 1 / (float) pasosU) //u=1 es igual a u=0 en siguiente curva
			ptos.push_back(calcularPuntoBezier(u, perfil));
	}
	ptos.push_back(calcularPuntoBezier(1, perfil));
	vertices.push_back(ptos);
}

btVector3 SuperficieRevolucion::calcularPuntoBezier(float u, vectorPuntos ctrlPts) {
	btVector3 punto(0,0,0);
	int n = GRADO_BEZIER;
	for (unsigned i = 0; i < ctrlPts.size(); i++) {
		float c = factorial(n) /(factorial(i) * factorial(n - i)) * pow(u,i) * pow(1-u,n-i);
		punto += c * ctrlPts[i];
	}
	return punto;
}

void SuperficieRevolucion::draw() {
	glBegin( GL_TRIANGLE_STRIP);
	for (unsigned i = 0; i < vertices.size() ; i++) {
		for (unsigned j = 0; j < vertices[i].size(); j++) {
			glNormal3fv(normales[i][j]);
			glVertex3fv(vertices[i][j]);
			glNormal3fv(normales[fmod(i + 1, vertices.size())][j]);
			glVertex3fv(vertices[fmod(i + 1, vertices.size())][j]);
		}
	}
	glEnd();
}

int SuperficieRevolucion::factorial(int n) {
	int resultado = 1;
	for (int i = 2; i <= n; i++)
		resultado = resultado * i;
	return resultado;
}
