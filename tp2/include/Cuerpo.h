#ifndef CUERPO_H_INCLDED
#define CUERPO_H_INCLDED

class Cuerpo{
  //Shader vertexShader;
  //Shader fragmentShader;
  
  protected:
  int ancho, alto;
  float r,g,b;
  virtual void do_dibujar()=0;
public:
  Cuerpo();
  void dibujar();
  void setColor(float r, float g, float b);
  int getAlto();
  int getAncho();
};

#endif
