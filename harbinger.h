#ifndef HARBINGER_H
#define HARBINGER_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class Harbinger : public Ship
{
private:
	short thrust;
public:
  	/***********************************************
  	* Constructors.
  	***********************************************/
  	Harbinger()
    {
     	type = 7;
    	rotation = 0;
      point.setX(0);
      point.setY(0);
      alive = true;
      flip = true;
    }
  
 	/***********************************************
  * Apply meathods: These meathods call the mutators for the velocity variable. 
  ***********************************************/
  void up()       { velocity.addDY(-.25 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.25 * cos((rotation - 90) / 57.2958)); thrust = 1; };
  void down()     { };
  void left()     { if (flip) rotation -= 5.5; else rotation += 5.5; };
  void right()    { if (flip) rotation += 5.5; else rotation -= 5.5; };
  void constant() { thrust = 0; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawHarbinger(point, rotation, thrust); };

};

#endif