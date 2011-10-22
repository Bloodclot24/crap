#include "Esfera.h"
#include <GL/glut.h>
#include <math.h>


typedef struct
{
    int X;
    int Y;
    int Z;
    double U;
    double V;
}VERTICES;

const int space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;

VERTICES VERTEX[VertexCount];



Esfera::Esfera(){
	construirEsfera(70);
}

void Esfera::do_dibujar(){
    //glutSolidSphere(0.5, 20, 20);
	mostrarEsfera(0.5/*,0*/);
}



void Esfera::mostrarEsfera (double R/*, GLuint texture*/)
{

    int b;
    glScalef (0.0125 * R, 0.0125 * R, 0.0125 * R);
    glRotatef (90, 1, 0, 0);
//    glBindTexture (GL_TEXTURE_2D, texture);
    glBegin (GL_TRIANGLE_STRIP);
    for ( b = 0; b < VertexCount; b++)
    {
       // glTexCoord2f (VERTEX[b].U, VERTEX[b].V);
        glNormal3f(VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
    }

    for ( b = 1; b < VertexCount; b++)
    {
        //glTexCoord2f (VERTEX[b].U, -VERTEX[b].V);
        glNormal3f(VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
    }

    glEnd();
}

void Esfera::construirEsfera (double R)
{
    int n;
    double a;
    double b;

    n =	0;

    for ( b = 0; b <= 90 - space; b+=space)
    {
        for ( a = 0; a <= 360 - space; a+=space)
        {
            VERTEX[n].X = R * sin((a) / 180 * M_PI) * sin((b) / 180 * PI);
            VERTEX[n].Y = R * cos((a) / 180 * M_PI) * sin((b) / 180 * PI);
            VERTEX[n].Z = R * cos((b) / 180 * M_PI);
            VERTEX[n].V = (2 * b) / 360;
            VERTEX[n].U = (a) / 360;
            n++;

            VERTEX[n].X = R * sin((a) / 180 * M_PI) * sin((b + space) / 180 * PI);
            VERTEX[n].Y = R * cos((a) / 180 * M_PI) * sin((b + space) / 180 * PI);

            VERTEX[n].Z = R * cos((b + space) / 180 * PI);
            VERTEX[n].V = (2 * (b + space)) / 360;
            VERTEX[n].U = (a) / 360;
            n++;

            VERTEX[n].X = R * sin((a + space) / 180 * M_PI) * sin((b) / 180 * PI);
            VERTEX[n].Y = R * cos((a + space) / 180 * M_PI) * sin((b) / 180 * PI);

            VERTEX[n].Z = R * cos((b) / 180 * M_PI);
            VERTEX[n].V = (2 * b) / 360;
            VERTEX[n].U = (a + space) / 360;

            n++;

            VERTEX[n].X = R * sin((a + space) / 180 * M_PI) * sin((b + space) / 180 * PI);
            VERTEX[n].Y = R * cos((a + space) / 180 * M_PI) * sin((b + space) / 180 * PI);
            VERTEX[n].Z = R * cos((b + space) / 180 * M_PI);
            VERTEX[n].V = (2 * (b + space)) / 360;
            VERTEX[n].U = (a + space) / 360;

            n++;
        }
    }
}
