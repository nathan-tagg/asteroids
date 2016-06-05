#ifndef ROCK_H
#define ROCK_H

#include "flyingObject.h"

class Rock : public FlyingObject
{
protected:
	short size;
	short immortal;
public:
	short getSize() { return size; };
	void setVelocity(Velocity v) { velocity = v; };
	short isImmortal() { return immortal; };

};

#endif