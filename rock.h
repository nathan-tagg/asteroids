#ifndef ROCK_H
#define ROCK_H

#include "flyingObject.h"

class Rock : public FlyingObject
{
protected:
	int size;
	int immortal;
public:
	int getSize() { return size; };
	void setVelocity(Velocity v) { velocity = v; };
	int isImmortal() { return immortal; };

};

#endif