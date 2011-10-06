#include "Mundo.h"

#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

#define TOP_VIEW_POSX	((int)((float)W_WIDTH*0.60f))
#define TOP_VIEW_W	((int)((float)W_WIDTH*0.40f))
#define TOP_VIEW_POSY	((int)((float)W_HEIGHT*0.60f))
#define TOP_VIEW_H	((int)((float)W_HEIGHT*0.40f))

Mundo* Mundo::te_odio= NULL;

void Mundo::inicializar(){
    dl_handle = glGenLists(3);

    glClearColor(0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    // Generación de las Display Lists
    glNewList(DL_AXIS, GL_COMPILE);
    dibujarEjes();
    glEndList();
    glNewList(DL_GRID, GL_COMPILE);
    dibujarGrilla();
    glEndList();
    glNewList(DL_AXIS2D_TOP, GL_COMPILE);
    dibujarEjesVista2D();
    glEndList();
}

void Mundo::dibujarEjes(){
 glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    // X
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(15.0, 0.0, 0.0);
    // Y
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 15.0, 0.0);
    // Z
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 15.0);
    glEnd();
    glEnable(GL_LIGHTING); 
}

void Mundo::dibujarEjesVista2D(){
  glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
    // X
    glColor3f(0.0f, 0.5f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    glEnable(GL_LIGHTING);
}

void Mundo::dibujarGrilla(){
 int i;
    glDisable(GL_LIGHTING);
    glColor3f(0.25f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    for(i=-20; i<21; i++)
	{
	    glVertex3f((float)i, -20.0f, 0.0f);
	    glVertex3f((float)i,  20.0f, 0.0f);
	    glVertex3f(-20.0f, (float)i, 0.0f);
	    glVertex3f( 20.0f, (float)i, 0.0f);
	}
    glEnd();
    glEnable(GL_LIGHTING); 
}

void Mundo::entorno3D(){
 glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0); 
}

void Mundo::entornoPanel(){
    glViewport (TOP_VIEW_POSX, TOP_VIEW_POSY, (GLsizei) TOP_VIEW_W, (GLsizei) TOP_VIEW_H); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(-0.10, 1.05, -0.10, 1.05);
}

void Mundo::display(){
     glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///////////////////////////////////////////////////
    // Escena 3D
    entorno3D();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt (eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
    //glRotatef(Z, 0, 0, 1);
       
    if (view_axis)
	glCallList(DL_AXIS);
	
    if (view_grid)
	glCallList(DL_GRID);
    //
    ///////////////////////////////////////////////////

	
    
    ///////////////////////////////////////////////////
    // Panel 2D para la vista superior
    if (edit_panel){
	    entornoPanel();
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);
	    glCallList(DL_AXIS2D_TOP);
    }
    //
    ///////////////////////////////////////////////////
    glutSwapBuffers(); 
}

void Mundo::reshape (int w, int h)
{
    W_WIDTH  = (float)w;
    W_HEIGHT = (float)h;
}

void Mundo::keyboard(unsigned char key, int x, int y){
  std::cout << "Tecla " << key << "\n";
      if(teclas[key]->press())
	 glutPostRedisplay();
}

void Mundo::display_static(){
    te_odio->display();
}

void Mundo::reshape_static(int x, int y){
    te_odio->reshape(x,y);
}

void Mundo::keyboard_static(unsigned char key, int x, int y){
    te_odio->keyboard(key, x ,y);
}

Mundo::Mundo(int argc, char** argv) {
    eye[0] = 15;
    eye[1] = 15;
    eye[2] = 5;
    
    at[0] = 0;
    at[1] = 0;
    at[2] = 3;
    
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;

    light_color[0] = 1;
    light_color[1] = 1;
    light_color[2] = 1;
    light_color[3] = 1;
    
    light_position[0] = 10;
    light_position[1] = 10;
    light_position[2] = 8;
    
    light_ambient[0] = 0.05;
    light_ambient[1] = 0.05;
    light_ambient[2] = 0.05;
    light_ambient[3] = 1;
    
    nombreMundo = argv[0];
    
    view_axis = 1;
    view_grid = 1;
    edit_panel = 0;
    
    glutInit(&argc, argv);
}

void Mundo::crearVentana(int w, int h, int flags) {
    glutInitDisplayMode(flags);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(nombreMundo.c_str());
}

void Mundo::comenzar() {
    inicializar();
    te_odio = this;
    glutDisplayFunc(Mundo::display_static);
    glutReshapeFunc(Mundo::reshape_static);
    glutKeyboardFunc(Mundo::keyboard_static);
    //glutPassiveMotionFunc(Mundo::pmotion_static);
    glutMainLoop();
}

void Mundo::cambiarVisibilidadPanel(){
    edit_panel = !edit_panel;
}


void Mundo::agregarTecla(char tecla, ManejadorTecla *manejador){
  manejador->setMundo(this);
  teclas[tecla] = manejador;
}