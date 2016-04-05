#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
	float dX;
	float dY;

public:
	Velocity() { dX = 0; dY = 0;};
	Velocity(float x, float y) { dX = x; dY = y; };
	void setDX(float x) { dX = x; };
	void setDY(float y) { dY = y; };
	void addDX(float x) { dX += x; };
	void addDY(float y) { dY += y; };
	float getDX() { return dX; };
	float getDY() { return dY; };
};

#endif
