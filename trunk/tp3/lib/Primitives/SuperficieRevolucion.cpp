#include "Primitives/SuperficieRevolucion.h"
#include "Curves/Bezier.h"

#include <GL/glu.h>

SuperficieRevolucion::SuperficieRevolucion(Bezier perfil, unsigned rotaciones, 
                                           unsigned pasosT, unsigned grados, 
                                           btVector3 axis){

    bezier_ = perfil;
    vectorPuntos puntos = discretizarBezier(pasosT);

    for (unsigned i = 0; i < rotaciones; i++) {
        vectorPuntos puntosRotados;
        for (unsigned j = 0; j < puntos.size(); j++){
            puntosRotados.push_back(puntos[j].rotate(axis, 2*M_PI*i / rotaciones));
        }
        vertices.push_back(puntosRotados);
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

vectorPuntos SuperficieRevolucion::discretizarBezier(unsigned pasosT) {
    vectorPuntos puntos;
    
    for (float t = 0; t < 1; t += 1 / (float) pasosT)
        puntos.push_back(bezier_.getPoint(t));

    return puntos;
}



void SuperficieRevolucion::drawPrimitive() {
    glBegin( GL_TRIANGLE_STRIP);
    float height_ = 26.5;

    float pasosi = vertices.size() - 1;
    float pasosj = vertices[0].size() - 1;
    for (int i = 0; i <= pasosi ; i++) {
        for (int j = 0; j <= pasosj; j++) {
            glNormal3fv(normales[i][j]);
            glTexCoord2f(i/pasosi,vertices[i][j][2]/height_);

            glVertex3fv(vertices[i][j]);

            glNormal3fv(normales[fmod(i + 1, pasosi)][j]);
            glTexCoord2f((i+1)/pasosi,vertices[i][j][2]/height_);
            glVertex3fv(vertices[fmod(i + 1, pasosi)][j]);

        }
        glVertex3fv(vertices[fmod(i + 1, pasosi)][pasosj]);
    }

    glEnd();
}
