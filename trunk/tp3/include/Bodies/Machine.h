#ifndef MACHINE_H_
#define MACHINE_H_

#include "Body.h"
#include "Bodies/Prism.h"
#include "Bodies/Bottle.h"

#include <vector>

class Machine: public Body {
protected:
    std::vector<Prism> prism_;

public:
	Machine();
	virtual bool process(Bottle* bottle, float step);
	virtual ~Machine();
};

#endif /* MACHINE_H_ */
