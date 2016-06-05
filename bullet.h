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
	short life;
	short type;
	short rotation;
public:
	Bullet() {};
	~Bullet() 
	{
		if (type != 3 && type != 10 && type != 4)
		{
			drawBoom(point, 3);
		}
	};
	void fire(short tipo, short direction)
	{
		type = tipo;
		alive = true; 
		rotation = direction + 270; 
		life = 60;
		if (tipo == 1)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 6); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 6); 
		}
		if (tipo == 2)
		{
			velocity.addDX(0); 
			velocity.addDY(-3); 
			life = 150;
		}
		
		if (tipo == 3)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 9); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 9);
			life =  90;
		}

		if (tipo == 4 || tipo == 6)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 3); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 3);
		}
		if (tipo == 5)
			life = 2000;
		if (tipo == 7)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 10 + random (-1.0, 1.0)); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 10 + random (-1.0, 1.0));
			life =  100;
		}
		if (tipo == 8)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 20); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 20);
			life = 10000;
		}
		if (tipo == 9)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 10); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 10);
			life =  100;			
		}
		if (tipo == 10)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 9); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 9);
			life = 90;			
		}
		if (tipo == 12)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 20); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 20);
			life = 1000;
		}
		if (tipo == 11)
		{
			velocity.addDX(cos(0.0174533 * (direction + 90)) * 9); 
			velocity.addDY(sin(0.0174533 * (direction + 90)) * 9);
			life =  90;
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
		if (type != 3 && type != 4 && type != 6 && type != 7 && type != 9 && type != 10)		
			rotation += 5;
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
		else if (type == 4 && life < 55 || type == 6)
			drawDot(point);
		else if (type == 5)
		{
			drawPolygon(point, 5, 3, rotation);
			drawPolygon(point, 5, 3, -rotation);
			drawTeleport(point, 4);
		}
		else if (type == 7)
		{
			drawGreenDot(point);
		}
		else if (type == 8)
		{
			drawBolt(point, 6, 3, rotation);
			drawBolt(point, 6, 3, -rotation);
		}
		else if (type == 9)
		{
			drawBolt(point, 7, 2, rotation);
		}
		else if (type == 10 || type == 11)
			drawBolt(point, 4, 2, rotation); 
		else if (type == 12)
			drawBoom(point, 3);

		else
		{}
	};
	virtual void kill() 
	{ 
		if (type != 3 && type != 10 && type != 5 && type != 9) 
		    alive = false; 
    };
	short getType() { return type; };
	short getLife() { return life; };
	void stop() { velocity.setDX(0); velocity.setDY(0); }; 
};
#endif
