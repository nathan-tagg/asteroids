#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class FlyingObject
{
protected:
	bool alive;
	Point point;
	Velocity velocity;

public:
	bool isAlive() { return alive; };
	virtual void advance() 
	{ 
		point.addX(velocity.getDX()); 
		point.addY(velocity.getDY());
		if (point.getX() > 700 || point.getX() < -700)
			wrapSides();
		if (point.getY() > 500 || point.getY() < -500)
			wrapUpDown();
		draw(); 
	};
	virtual void draw() = 0;
	void setPoint(Point p) { point = p;                                         };
	Point getPoint() { return point;                                            };
	Velocity getVelocity() { return velocity;                                   };
	void setVelocity(Velocity v) { velocity = v;                                };
	void setVelocity(float x, float y) { velocity.setDX(x); velocity.setDY(y);  };
	void addVelocity(float x, float y) { velocity.addDX(x); velocity.addDY(y);  };
	virtual void kill() { alive = false;                                        };
	void wrapSides() { point.setX(-point.getX()); 				     			};
	void wrapUpDown() { point.setY(-point.getY());		       					};
	void reset() { point.setX(0); point.setY(0); velocity.setDX(0); velocity.setDY(0); };
};

#endif