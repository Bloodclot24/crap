#ifndef CUERPO_H_INCLDED
#define CUERPO_H_INCLDED

class Cuerpo{
  //Shader vertexShader;
  //Shader fragmentShader;
  
  protected:
  virtual void do_dibujar()=0;
public:
  void dibujar();
};

#endif
