#ifndef COMANDOCAMBIARFORMA_H_INCLUDED
#define COMANDOCAMBIARFORMA_H_INCLUDED
#include "Command.h"

//Odio tener que hacer esto...
class ComandoCambiarFormaEsfera: public Command{
    virtual void ejecutar();
};

class ComandoCambiarFormaCubo: public Command{
    virtual void ejecutar();
};

class ComandoCambiarFormaToroide: public Command{
    virtual void ejecutar();
};

class ComandoCambiarFormaCilindro: public Command{
    virtual void ejecutar();
};

class ComandoCambiarFormaCono: public Command{
    virtual void ejecutar();
};

#endif
