#ifndef HUGEROCK_H
#define HUGEROCK_H

#include "flyingObject.h"
#include "rock.h"

#include <math.h>

class HugeRock : public Rock
{
private:
	short rotation;
	short angle;
	short direction;
	short spin;

public:
	HugeRock() 
	{ 
		alive = true;
		direction = random(0, 2);
		angle = random(0, 360);
		velocity.setDX(cos(angle) * 2); 
		velocity.setDY(sin(angle) * 2); 
		rotation = random(-100, 100);
		spin = random(.5, 1.0); 
		size = 50;
		immortal = 40;
	};
	void draw() 
	{ 	
		if (immortal)
		{
			drawHugeAsteroid(point, rotation, 1, 0 ,0);
			immortal--;
		}
		else
			drawHugeAsteroid(point, rotation, 1, 1, 1); 
		if (direction == 1)
			rotation += spin; 
		else
			rotation -= spin;
			alive = false;

	};
	virtual void kill() { drawHugeAsteroid(point, rotation, 1, 0, 0); };
};

#endif