#ifndef TANK_H
#define TANK_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class Tank : public Ship
{
private:
	int thrust;
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
  void up()       { velocity.addDY(-.4 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.4 * cos((rotation - 90) / 57.2958)); thrust = 1; };
  void down()     
  { 
    if (velocity.getDX() < 0) 
      velocity.addDX(.2); 
    else if (velocity.getDX() > 0)
      velocity.addDX(-.2);
    if (velocity.getDY() < 0)
      velocity.addDY(.2); 
    else if (velocity.getDY() > 0)
      velocity.addDY(-.2);
  };
  void left()     { if (flip) { rotation -= 12; } else { rotation += 12; } };
  void right()    { if (flip) { rotation += 12; } else { rotation -= 12; } };
  void constant() { thrust = 0; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawTank(point, rotation, thrust); };


};

#endif