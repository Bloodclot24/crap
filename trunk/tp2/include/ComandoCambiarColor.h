#ifndef COMANDOCAMBIARCOLOR_H_INCLUDED
#define COMANDOCAMBIARCOLOR_H_INCLUDED

#include "Command.h"

class ComandoCambiarColor:public Command{
private:
  float r,g,b;
public:
  
  ComandoCambiarColor(float r, float g, float b);
  virtual void ejecutar();
};

#endif
