#ifndef OLDY_H
#define OLDY_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class Oldy : public Ship
{
private:
	int thrust;
  bool secret;
public:
  	/***********************************************
  	* Constructors.
  	***********************************************/
  	Oldy()
    {
     	type = 6;
    	rotation = 0;
      point.setX(0);
      point.setY(0);
      alive = true;
      flip = true;
    }
  
 	/***********************************************
  * Apply meathods: These meathods call the mutators for the velocity variable. 
  ***********************************************/
  void up()       { velocity.addDY(-.15 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.15 * cos((rotation - 90) / 57.2958)); thrust = 1; };
  void down()     { secret = true; };
  void left()     { if (flip) rotation -= 3; else rotation += 3; };
  void right()    { if (flip) rotation += 3; else rotation -= 3; };
  void constant() { thrust = 0; secret = false; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawOldShip(point, rotation, thrust); };
  bool ultimateDestruction() { return secret; };


};

#endif