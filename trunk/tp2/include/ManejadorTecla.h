#ifndef MANEJADORTECLA_H_INCLUDED
#define MANEJADORTECLA_H_INCLUDED

class Mundo;

class ManejadorTecla{
protected:
  Mundo* mundo;
public:
  void setMundo(Mundo *m){
    mundo = m;
  }
  virtual bool press(){return false;};
};

#endif
