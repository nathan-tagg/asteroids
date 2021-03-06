#ifndef SPACER_H
#define SPACER_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class Spacer : public Ship
{
private:
	short thrust;
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
  void up()       { velocity.addDY(-.2 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.2 * cos((rotation - 90) / 57.2958)); thrust = 1; };
  void down()     { velocity.addDY(-.6 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.6 * cos((rotation - 90) / 57.2958)); thrust = 2; };
  void left()     { if (flip) rotation -= 5.0; else rotation += 5.0; };
  void right()    { if (flip) rotation += 5.0; else rotation -= 5.0; };
  void constant() { thrust = 0; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawShip(point, rotation, thrust); };


};

#endif