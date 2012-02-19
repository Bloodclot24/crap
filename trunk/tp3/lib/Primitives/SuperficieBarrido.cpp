#include "Primitives/SuperficieBarrido.h"
#include <GL/glu.h>

SuperficieBarrido::SuperficieBarrido(vectorPuntos perfil, vectorPuntos normales, 
                                     BSpline bspline, unsigned pasosU): 
    ptosPerfil(perfil), normalesPerfil(normales), bspline_(bspline) {

    cargarCoordenadasBSpline(pasosU);
    cargarCoordenadas();
}

SuperficieBarrido::~SuperficieBarrido() {
}

void SuperficieBarrido::cargarCoordenadas() {
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
    for (float t = 0; t < 1; t += 1 / (float) pasosU) {
        ptosCurva.push_back(bspline_.getPoint(t));
        tgsCurva.push_back(bspline_.getTangent(t));
    }
}

void SuperficieBarrido::drawPrimitive() {
    glBegin(GL_TRIANGLE_STRIP);
    float pasosi = vertices.size() - 1;
    float pasosj = vertices[0].size() - 1;
    for (int i = 0; i < pasosi ; i++) {
        for (int j = 0; j <= pasosj; j++) {

            glNormal3fv(normales[i][j]);
            glTexCoord2f( j /pasosj, i/pasosi*20);
            glVertex3fv(vertices[i][j]);

            glNormal3fv(normales[i + 1][j]);
            glTexCoord2f( j /pasosj, (i+1)/pasosi*20);
            glVertex3fv(vertices[i + 1][j]);
        }
    }
    glEnd();
}
