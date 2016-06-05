#ifndef UFO_H
#define UFO_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class Ufo : public Ship
{
private:
public:
  	/***********************************************
  	* Constructors.
  	***********************************************/
  	Ufo()
    {
     	type = 11;
    	rotation = 0;
      point.setX(0);
      point.setY(0);
      alive = true;
      flip = true;
    }
  
 	/***********************************************
  * Apply meathods: These meathods call the mutators for the velocity variable. 
  ***********************************************/
  void up()       { point.addY(2); rotation -= 3; };
  void down()     { point.addY(-2); rotation += 3; };
  void left()     { point.addX(-2); rotation += 3; };
  void right()    { point.addX(2); rotation -= 3; };
  void constant() {  };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawUFO(point, rotation); };


};

#endif