#ifndef _LASTMACHINE_H_
#define _LASTMACHINE_H_

#include "Machine.h"

class LastMachine : public Machine
{
    std::vector<Prism> ramp_;

	void drawRamp();
	void createRamp();

public:
    LastMachine();
    void draw();
    Prism& getRamp(){
    	return ramp_[0];
    }
    virtual ~LastMachine();
};

#endif /* _LASTMACHINE_H_ */
