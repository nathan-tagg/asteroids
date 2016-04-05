#ifndef HUGEROCK_H
#define HUGEROCK_H

#include "flyingObject.h"
#include "rock.h"

#include <math.h>

class HugeRock : public Rock
{
private:
	int rotation;
	float angle;
	int direction;
	int spin;
	int cracks;

public:
	HugeRock() 
	{ 
		alive = true;
		direction = random(0, 2);
		angle = random(0.00, 360.00);
		velocity.setDX(cos(angle) * 2); 
		velocity.setDY(sin(angle) * 2); 
		rotation = random(-100, 100);
		spin = random(1, 2); 
		size = 50;
		immortal = 40;
		cracks = 0;
	};
	void draw() 
	{ 	
		if (immortal)
		{
			drawHugeAsteroid(point, rotation, 1, 0 ,0, cracks);
			immortal--;
		}
		else
			drawHugeAsteroid(point, rotation, 1, 1, 1, cracks); 
		if (direction == 1)
			rotation += spin; 
		else
			rotation -= spin;
		if (cracks > 3)
			alive = false;

	};
	virtual void kill() { cracks++; drawHugeAsteroid(point, rotation, 1, 0, 0, cracks); };
};

#endif