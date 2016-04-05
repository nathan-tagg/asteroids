#ifndef Sniper_H
#define Sniper_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"
#include "point.h"

class Sniper : public Ship
{
private:
	int thrust;
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
  void up()       { velocity.addDY(-.3 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.3 * cos((rotation - 90) / 57.2958)); thrust = 1; };
  void down()     {};
  void left()     
  {
    if (scope)
    { 
      if ( flip )
        rotation += 1.0;
      else
        rotation -= 1.0;
    }
    else
    {
      if ( flip )
        rotation += 8.0;
      else
        rotation -= 8.0;
    }
  };
  void right()    
  {
    if (scope)
    { 
      if ( flip )
        rotation -= 1.0;
      else
        rotation += 1.0;
    }
  else
  {
    if ( flip )
      rotation -= 8.0;
    else
      rotation += 8.0;
  }
  };
  void constant() { thrust = 0; };
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawSniper(point, rotation, thrust, scope); };
  void activateScope() { scope = !scope; };
};

#endif