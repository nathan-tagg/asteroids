#ifndef SMALLROCK_H
#define SMALLROCK_H

#include "flyingObject.h"
#include "rock.h"

#include <math.h>

class SmallRock : public Rock
{
private:
	int rotation;
	float angle;
	int direction;
	int spin;

public:
	SmallRock() 
	{ 
		alive = true;
		direction = random(0, 2);
		angle = random(0.00, 360.00);
		velocity.setDX(cos(angle) * 2); 
		velocity.setDY(sin(angle) * 2); 
		rotation = random(-100, 100);
		spin = random(7, 11); 
		size = 9;
		immortal = 20;
	};
	void draw() 
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