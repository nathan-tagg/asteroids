#ifndef SPACER_H
#define SPACER_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class Spacer : public Ship
{
private:
	int thrust;
public:
  	/***********************************************
  	* Constructors.
  	***********************************************/
  	Spacer()
    {
     	type = 1;
    	rotation = 0;
      point.setX(0);
      point.setY(0);
      alive = true;
      flip = true;
    }
  
 	/***********************************************
  * Apply meathods: These meathods call the mutators for the velocity variable. 
  ***********************************************/
  void up()       { velocity.addDY(-.5 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.5 * cos((rotation - 90) / 57.2958)); thrust = 1; };
  void down()     { velocity.addDY(-1.5 * sin((rotation - 90) / 57.2958)); velocity.addDX(-1.5 * cos((rotation - 90) / 57.2958)); thrust = 2; };
  void left()     { if (flip) rotation -= 10; else rotation += 10; };
  void right()    { if (flip) rotation += 10; else rotation -= 10; };
  void constant() { thrust = 0; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawShip(point, rotation, thrust); };


};

#endif