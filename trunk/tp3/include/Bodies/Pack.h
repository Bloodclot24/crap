#ifndef PACK_H_
#define PACK_H_

#include "Body.h"
#include "Bodies/Bottle.h"

#include <vector>

class Pack: public Body {
	std::vector<Bottle*> bottles_;
public:
	Pack();
	void draw();
	void addBottle(Bottle* bottle);
	int getBottlesCount();
	virtual ~Pack();
};

#endif /* PACK_H_ */
