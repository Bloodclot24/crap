///
/// 66.71 Sistemas Graficos
/// Framework de trabajo para el TP1
/// 2do Cuatrimestre 2011
///
/// info@sg6671.com.ar
///

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

int tiempo = 0;
int niveles = 8;
int incremento_tiempo = 1;
int incremento_anterior = 0;
bool animacion_corriendo = true;
float Z = 0;
bool mouse_capturado = false;
int x_mouse = 0, y_mouse = 0;
int tiempo_max = niveles * 10;

// Variables que controlan la ubicaci�n de la c�mara en la Escena 3D
float eye[3] = {15.0, 15.0, 5.0};
float at[3]  = { 0.0,  0.0, 3.0};
float up[3]  = { 0.0,  0.0, 1.0};

// Variables asociadas a �nica fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};

// Color de la esfera en movimiento dentro de la escena
float color_esfera[4] = {0.5f, 0.5f, 0.2f, 1.0f};

// Variable asociada al movimiento de rotaci�n de la esfera alrededor del eje Z
float rotate_sphere = 0;

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool edit_panel = false;

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

// Tama�o de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

#define TOP_VIEW_POSX	((int)((float)W_WIDTH*0.60f))
#define TOP_VIEW_W		((int)((float)W_WIDTH*0.40f))
#define TOP_VIEW_POSY	((int)((float)W_HEIGHT*0.60f))
#define TOP_VIEW_H		((int)((float)W_HEIGHT*0.40f))

void OnIdle (void)
{
    rotate_sphere += 0.1f;
    if(rotate_sphere > 360.0) rotate_sphere = 0.0;
    //glutPostRedisplay();
}

void DrawAxis()
{
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

void DrawAxis2DTopView()
{
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


void DrawXYGrid()
{
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

void Set3DEnv()
{
    glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0);
}

void SetPanelTopEnv()
{
    glViewport (TOP_VIEW_POSX, TOP_VIEW_POSY, (GLsizei) TOP_VIEW_W, (GLsizei) TOP_VIEW_H); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(-0.10, 1.05, -0.10, 1.05);
}


void init(void) 
{
    dl_handle = glGenLists(3);

    glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    // Generaci�n de las Display Lists
    glNewList(DL_AXIS, GL_COMPILE);
    DrawAxis();
    glEndList();
    glNewList(DL_GRID, GL_COMPILE);
    DrawXYGrid();
    glEndList();
    glNewList(DL_AXIS2D_TOP, GL_COMPILE);
    DrawAxis2DTopView();
    glEndList();
}

void dibujarRombo(){
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(-10, -10, -8);
    glVertex3f(0, -0.25, -0.5);
    glVertex3f(0, -0.25, 0);
    glVertex3f(0, 0.25, 0);
    glVertex3f(0, 0.25, 0.5);
    glEnd();
}

void dibujarCirculo(int segmentos){
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos)
	glVertex3f(cos(i), sin(i), 0);
    glEnd();
}

void dibujarCilindro(int segmentos, float radio_superior = 1){
    static GLint lista = 0;
    static bool compilada = false;

    if(!compilada){
	lista=glGenLists(1);
	glNewList(lista, GL_COMPILE);
  
	glBegin(GL_TRIANGLE_STRIP);
	for(float i = 0; i <= 2*M_PI; i += 2*M_PI / segmentos){
	    float _cos = cos(i);
	    float _sin = sin(i);
	    glNormal3f(_cos, _sin, 0);
	    glVertex3f(_cos, _sin, -0.5);
	    glVertex3f(_cos*radio_superior, _sin*radio_superior, 0.5);
	}
	glEnd();
  
	//Dibujo las tapas
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glScalef(radio_superior, radio_superior, 1);
	dibujarCirculo(segmentos);
	glPopMatrix();
  
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glRotatef(180, 1, 0, 0);
	dibujarCirculo(segmentos);
	glPopMatrix();

	glEndList();
	compilada=true;
    }

    glCallList(lista);
}

void dibujarHoja() {
    static GLint lista = 0;
    static bool compilada=false;

    if(!compilada){
	lista=glGenLists(1);
	glNewList(lista, GL_COMPILE);

	glColor3f(0,0.5,0);
 	dibujarRombo();     
	glEndList();
	compilada=true;
    }

    glCallList(lista);

}

void dibujarRama(float altura){
 
    float radio = 0.04*altura;
    glPushMatrix(); 
    glScalef(radio, radio, altura);
    glTranslatef(0, 0, 0.5);
    glColor3f(0.58,0.26,0);
    dibujarCilindro(6, 0.5);
    glPopMatrix();
}  

void dibujarArbol(int profundidad, float z, float angulo, int ejex, int ejey, int ejej) {

    glPushMatrix();
    glTranslatef(0, 0, z);
    glRotatef(angulo, ejex, ejey, ejej);
   
    if(profundidad > 0) {
	float crecimiento = 0.1*(2*profundidad - 1) * (tiempo % 10)/10;
	float altura = 0.1 * (profundidad - 1) * (profundidad - 1) + crecimiento;
	dibujarRama(altura);
        profundidad--;
	glRotatef(90, 0, 0, 1);
	dibujarArbol(profundidad, 0.5*altura, 40 + profundidad, 1, 0, 0);
	dibujarArbol(profundidad, 0.5*altura, -(40 + profundidad), 1, 0, 0);
	dibujarArbol(profundidad, altura, 30 + profundidad, 0, 1, 0);
	dibujarArbol(profundidad, altura, -(30 + profundidad), 0, 1, 0);
    } else {
	glScalef(0.25, 0.25, 0.25);
	dibujarHoja();
    }
    glPopMatrix();
}

void incrementar_tiempo(int a){
    if ( tiempo + incremento_tiempo <= tiempo_max) 
	tiempo += incremento_tiempo;
    else 
	tiempo = tiempo_max;
    glutPostRedisplay();
}
 
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///////////////////////////////////////////////////
    // Escena 3D
    Set3DEnv();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt (eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
    glRotatef(Z, 0, 0, 1);
    
    
   
    if (view_axis)
	glCallList(DL_AXIS);
	
    if (view_grid)
	glCallList(DL_GRID);
    //
    ///////////////////////////////////////////////////

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    dibujarArbol(tiempo/10,0,0,0,1,0);
    if(animacion_corriendo && tiempo < tiempo_max)
	glutTimerFunc(10, incrementar_tiempo,0);

    ///////////////////////////////////////////////////
    // Panel 2D para la vista superior
    if (edit_panel)
	{
	    SetPanelTopEnv();
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);
	    glCallList(DL_AXIS2D_TOP);
	}
    //
    ///////////////////////////////////////////////////
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    W_WIDTH  = (float)w;
    W_HEIGHT = (float)h;
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
	exit(0);
	break;

    case 'g':
	view_grid = !view_grid;
	glutPostRedisplay();
	break;

    case 'a':
	view_axis = !view_axis;
	glutPostRedisplay();
	break;

    case 'e':
	edit_panel = !edit_panel;
	glutPostRedisplay();
	break;

    case '2':
	eye[0] = 0.0;
	eye[1] = 0.0;
	eye[2] = 15.0;

	at[0] = 0.0;
	at[1] = 0.0;
	at[2] = 0.0;

	up[0] = 0.0;
	up[1] = 1.0;
	up[2] = 0.0;
	glutPostRedisplay();
	break;

    case 'A':
	if (animacion_corriendo && incremento_tiempo > 0)
	    incremento_tiempo--;
	
	break;
    case 'Q':
	if (animacion_corriendo)
	    incremento_tiempo++;
	
	break;
	
    case 'c':
      if(mouse_capturado){
	mouse_capturado = false;
	glutSetCursor(GLUT_CURSOR_INHERIT);
      }
      else{
	glutSetCursor(GLUT_CURSOR_NONE);
	mouse_capturado = true;
      }
      break;

    case 'P':
	if ( animacion_corriendo) {       
	    incremento_anterior = incremento_tiempo;		
	    incremento_tiempo = 0;
	    animacion_corriendo = false;
	} else {
	    incremento_tiempo = incremento_anterior;
	    animacion_corriendo = true;
	    glutPostRedisplay();
	}
	break;

    case 'R':
	tiempo = 0;
	glutPostRedisplay();
	break;

    case 'z':
	Z -=2;
	glutPostRedisplay();

	break;
    case 'Z':
	Z +=2;
	glutPostRedisplay();
	break;
    
    case 0x2B://+
	if(eye[0] > 1.0 && eye[1] > 1.0){
		eye[0]--;
		eye[1]--;
	}	
	glutPostRedisplay();
	break;

    case 0x2D://-
	eye[0]++;
	eye[1]++;
	glutPostRedisplay();
	break;


    case '3':
	eye[0] = 15.0;
	eye[1] = 15.0;
	eye[2] = 5.0;

	at[0] = 0.0;
	at[1] = 0.0;
	at[2] = 3.0;

	up[0] = 0.0;
	up[1] = 0.0;
	up[2] = 1.0;
	glutPostRedisplay();
	break;
    default:
	break;
    }
}

void motion(int x, int y){
  if(mouse_capturado){
      if(x_mouse < x)
	Z +=2;
      else if(x_mouse > x)
	Z -= 2;
      x_mouse=x;
      glutPostRedisplay();
      if(x<W_WIDTH/3 || x > 2*W_WIDTH/3){
	x_mouse = W_WIDTH/2;
	glutWarpPointer(x_mouse, W_HEIGHT/2);
      }
  }
}

int main(int argc, char** argv)
{

    if(argc > 1) {
	niveles = atoi(argv[1]);
	tiempo_max = niveles * 10;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1024, 768); 
    glutInitWindowPosition (0, 0);
   
    glutCreateWindow (argv[0]);
    //glutFullScreen();
    init ();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(motion);
    glutMainLoop();
    return 0;
}
