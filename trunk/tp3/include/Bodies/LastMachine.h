#ifndef _LASTMACHINE_H_
#define _LASTMACHINE_H_

#include "Machine.h"
#include "Primitives/SuperficieBarrido.h"

class LastMachine : public Machine
{
	SuperficieBarrido* rampa;
	void crearRampa();

public:
    LastMachine();
    void draw();
    virtual ~LastMachine();
};

#endif /* _LASTMACHINE_H_ */
