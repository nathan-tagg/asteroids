#ifndef LARGEROCK_H
#define LARGEROCK_H

#include "flyingObject.h"
#include "rock.h"

#include <math.h>

class LargeRock : public Rock
{
private:
	short rotation;
	short angle;
	short direction;
	short spin;

public:
	LargeRock() 
	{ 
		alive = true;
		direction = random(0, 2);
		angle = random(0, 360);
		velocity.setDX(cos(angle) * .5); 
		velocity.setDY(sin(angle) * .5); 
		rotation = random(-100, 100);
		spin = random(1,3); 
		size = 18;
		immortal = 80;
	};
	virtual void draw() 
	{ 	
		if (immortal)
		{
			drawLargeAsteroid(point, rotation, 1, 0 ,0);
			immortal--;
		}
		else
			drawLargeAsteroid(point, rotation, 1, 1, 1); 
		if (direction == 1)
			rotation += spin; 
		else
			rotation -= spin;

	};
};

#endif
