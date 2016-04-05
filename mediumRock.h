#ifndef MEDIUMROCK_H
#define MEDIUMROCK_H

#include "flyingObject.h"
#include "rock.h"

#include <math.h>

class MediumRock : public Rock
{
private:
	int rotation;
	float angle;
	int direction;
	int spin;

public:
	MediumRock() 
	{ 
		alive = true;
		direction = random(0, 2);
		angle = random(0.00, 360.00);
		velocity.setDX(cos(angle) * 2); 
		velocity.setDY(sin(angle) * 2); 
		rotation = random(-100, 100);
		spin = random(5,7); 
		size = 13;
		immortal = 20;
	};
	void draw() 
	{ 	
		if (immortal)
		{
			drawMediumAsteroid(point, rotation, 1, 0, 0);
			immortal--;
		}
		else
			drawMediumAsteroid(point, rotation, 1, 1, 1); 
		if (direction == 1)
			rotation += spin; 
		else
			rotation -= spin;

	};
};

#endif