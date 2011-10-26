#include "ComandoCompuesto.h"

void ComandoCompuesto::agregarComando(Command* c){
  comandos.push_back(c);
}
void ComandoCompuesto::ejecutar(){
  for(std::list<Command*>::iterator it = comandos.begin();
      it != comandos.end();
    it++){
      (*it)->ejecutar();
  }
}
