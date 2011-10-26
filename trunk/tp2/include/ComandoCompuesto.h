#ifndef COANDOCOMPUESTO_H_INCLUDED
#define COANDOCOMPUESTO_H_INCLUDED
#include "Command.h"
#include <list>

class ComandoCompuesto:public Command{
private:
  std::list<Command*> comandos;
  
public:
  void agregarComando(Command* c);
  virtual void ejecutar();
};


#endif
