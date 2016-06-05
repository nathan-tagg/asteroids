#ifndef SMALLROCK_H
#define SMALLROCK_H

#include "flyingObject.h"
#include "rock.h"

#include <math.h>

class SmallRock : public Rock
{
private:
	short rotation;
	short angle;
	short direction;
	short spin;

public:
	SmallRock() 
	{
		alive = true;
		direction = random(0, 2);
		angle = random(0, 360);
		velocity.setDX(cos(angle) * .5); 
		velocity.setDY(sin(angle) * .5); 
		rotation = random(-100, 100);
		spin = random(5, 7); 
		size = 9;
		immortal = 80;
	};
	virtual void draw() 
	{ 	
		if (immortal)
		{
			drawSmallAsteroid(point, rotation, 1, 0, 0);
			immortal--;
		}
		else
			drawSmallAsteroid(point, rotation, 1, 1, 1); 
		if (direction == 1)
			rotation += spin; 
		else
			rotation -= spin;
	};
};

#endif