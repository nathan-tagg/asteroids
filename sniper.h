#ifndef Sniper_H
#define Sniper_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"
#include "point.h"

class Sniper : public Ship
{
private:
	bool thrust;
  bool scope;
public:
  	/***********************************************
  	* Constructors.
  	***********************************************/
  	Sniper()
    {
     	type = 3;
    	rotation = 0;
      point.setX(0);
      point.setY(0);
      alive = true;
      scope = false;
    }
 	/***********************************************
  * Apply meathods: These meathods call the mutators for the velocity variable. 
  ***********************************************/
  void up()       { velocity.addDY(-.1 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.1 * cos((rotation - 90) / 57.2958)); thrust = true; };
  void down()     {};
  void left()     
  {
    if (scope)
    { 
      if ( flip )
        rotation += .5;
      else
        rotation -= .5;
    }
    else
    {
      if ( flip )
        rotation += 3.0;
      else
        rotation -= 3.0;
    }
  };
  void right()    
  {
    if (scope)
    { 
      if ( flip )
        rotation -= .5;
      else
        rotation += .5;
    }
  else
  {
    if ( flip )
      rotation -= 3.0;
    else
      rotation += 3.0;
  }
  };
  void constant() { thrust = false; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawSniper(point, rotation, thrust, scope); };
  void activateScope() { scope = !scope; };
};

#endif