#ifndef OLDY_H
#define OLDY_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class Oldy : public Ship
{
private:
	short thrust;
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
  void up()       { velocity.addDY(-.075 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.075 * cos((rotation - 90) / 57.2958)); thrust = false; };
  void down()     { secret = true; };
  void left()     { if (flip) rotation -= 2; else rotation += 2; };
  void right()    { if (flip) rotation += 2; else rotation -= 2; };
  void constant() { thrust = false; secret = false; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawOldShip(point, rotation, thrust); };
  bool ultimateDestruction() { return secret; };


};

#endif