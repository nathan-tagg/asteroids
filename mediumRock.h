#ifndef MEDIUMROCK_H
#define MEDIUMROCK_H

#include "flyingObject.h"
#include "rock.h"

#include <math.h>

class MediumRock : public Rock
{
private:
	short rotation;
	short angle;
	short direction;
	short spin;

public:
	MediumRock() 
	{ 
		alive = true;
		direction = random(0, 2);
		angle = random(0, 360);
		velocity.setDX(cos(angle) * .5); 
		velocity.setDY(sin(angle) * .5); 
		rotation = random(-100, 100);
		spin = random(3,5); 
		size = 13;
		immortal = 80;
	};
	virtual void draw() 
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