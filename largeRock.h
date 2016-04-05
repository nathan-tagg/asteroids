#ifndef LARGEROCK_H
#define LARGEROCK_H

#include "flyingObject.h"
#include "rock.h"

#include <math.h>

class LargeRock : public Rock
{
private:
	int rotation;
	float angle;
	int direction;
	int spin;

public:
	LargeRock() 
	{ 
		alive = true;
		direction = random(0, 2);
		angle = random(0.00, 360.00);
		velocity.setDX(cos(angle) * 2); 
		velocity.setDY(sin(angle) * 2); 
		rotation = random(-100, 100);
		spin = random(3,5); 
		size = 18;
		immortal = 20;
	};
	void draw() 
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
