#ifndef TANK_H
#define TANK_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class Tank : public Ship
{
private:
	bool thrust;
public:
  	/***********************************************
  	* Constructors.
  	***********************************************/
  	Tank()
    {
     	type = 4;
    	rotation = 0;
      point.setX(0);
      point.setY(0);
      alive = true;
      flip = true;
    }

 	/***********************************************
  * Apply meathods: These meathods call the mutators for the velocity variable. 
  ***********************************************/
  void up()       { velocity.addDY(-.2 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.2 * cos((rotation - 90) / 57.2958)); thrust = true; };
  void down()     
  { 
    if (velocity.getDX() < 0) 
      velocity.addDX(.1); 
    else if (velocity.getDX() > 0)
      velocity.addDX(-.1);
    if (velocity.getDY() < 0)
      velocity.addDY(.1); 
    else if (velocity.getDY() > 0)
      velocity.addDY(-.1);
    if (velocity.getDX() < .1 && velocity.getDX() > -.1)
    {
      velocity.setDX(0);
    }
    if (velocity.getDY() < .1 && velocity.getDY() > -.1)
    {
      velocity.setDY(0);
    }
  };
  void left()     { if (flip) { rotation -= 5; } else { rotation += 5; } };
  void right()    { if (flip) { rotation += 5; } else { rotation -= 5; } };
  void constant() { thrust = false; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawTank(point, rotation, thrust); };


};

#endif