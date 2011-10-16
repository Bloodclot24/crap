#include "Mundo.h"

Mundo* Mundo::te_odio= NULL;

void Mundo::reshape (int w, int h)
{
  ancho_ventana = w;
  alto_ventana = h;
}

void Mundo::display(){
  
}

void Mundo::keyboard(unsigned char key, int x, int y){
  std::cout << "Tecla " << key << "\n";
    if(teclas[key] != NULL)
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

Mundo* Mundo::get_instance(){
  if(te_odio == NULL)
    te_odio=new Mundo();
    
  return te_odio;
}

Mundo::Mundo() {
    nombreMundo = "GLUT";
    int argc=1;
    char* argv[] = {"GLUT", NULL};
    glutInit(&argc, argv);
}

void Mundo::crearVentana(int w, int h, int flags) {
    glutInitDisplayMode(flags);
    ancho_ventana=w; alto_ventana=h;
    glutInitWindowSize(w, h);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(nombreMundo.c_str());
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "Failed to initialize GLEW!" << std::endl;
    }
    std::cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
}

void Mundo::comenzar() {
    glutDisplayFunc(display_static);
    glutReshapeFunc(reshape_static);
    glutKeyboardFunc(keyboard_static);
    //glutPassiveMotionFunc(Mundo::pmotion_static);
    inicializar();
    glutMainLoop();
}

void Mundo::inicializar(){
  
}

void Mundo::agregarTecla(char tecla, ManejadorTecla *manejador){
  teclas[tecla] = manejador;
}
