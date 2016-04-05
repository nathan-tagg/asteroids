#ifndef BULLET_H
#define BULLET_H

#include "flyingObject.h"
#include "uiDraw.h"
#include "uiInteract.h"

#include <iostream>
#include <math.h>


using namespace std;

class Bullet : public FlyingObject
{
private:
	int life;
	int type;
	int rotation;
public:
	Bullet() {};
	void fire(int tipo, int direction)
	{
		type = tipo;
		alive = true; 
		rotation = direction + 270; 
		life = 40;
		if (tipo == 1)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 10); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 10); 
		}
		if (tipo == 2)
		{
			velocity.addDX(0); 
			velocity.addDY(-10); 
		}
		
		if (tipo == 3)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 25); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 25); 
		}

		if (tipo == 4 || tipo == 6)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 5); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 5);
			life = 30; 
		}
		if (tipo == 5)
			life = 500;
		if (tipo == 10)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 10); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 10);
			life = 100;			
		}
	}

	virtual void advance() 
	{ 
		point.addX(velocity.getDX()); 
		point.addY(velocity.getDY());
		if (point.getX() > 700 || point.getX() < -700)
			wrapSides();
		if (point.getY() > 500 || point.getY() < -500)
			wrapUpDown();
		if (type != 3 && type != 10)		
			rotation += 10;
		life--;
		if (life <= 0)
			alive = false;
		if (alive)
			draw(); 
	};
	virtual void draw() 
	{ 
		if (type == 1 || type == 2) 
			drawRound(point, rotation); 
		else if (type == 3) 
			drawPolygon(point, 6, 2, rotation); 
		else if (type == 4 && life < 28 || type == 6)
			drawDot(point);
		else if (type == 5)
		{
			drawPolygon(point, 5, 3, rotation);
			drawPolygon(point, 5, 3, -rotation);
			drawTeleport(point, 4);
		}
		else if (type == 10)
			drawBolt(point, 4, 2, rotation); 
	};
	virtual void kill() 
	{ 
		if (type != 3 && type != 10) 
		    alive = false; 
    };
	int getType() { return type; };
};

#endif
