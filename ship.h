#ifndef SHIP_H
#define SHIP_H

#include "flyingObject.h"

class Ship : public FlyingObject
{
protected:
	short type;
	float rotation;
	bool flip;
public:
   virtual void up() {};
   virtual void down() {};
   virtual void left() {};
   virtual void right() {};
   virtual void constant() {};
   virtual void advance() 
	{ 
		point.addX(velocity.getDX()); 
		point.addY(velocity.getDY());
		if (point.getX() > 700 || point.getX() < -700)
			wrapSides();
		if (point.getY() > 500 || point.getY() < -500)
			wrapUpDown();
		draw(); 
		constant();
	};
	short getType() { return type; };
	float getRotation() { return rotation; };
 	void setRotation(float r) { rotation = r; };
 	void invert() { flip = !flip; };

};
#endif /* SHIP_H */