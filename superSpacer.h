#ifndef SUPERSPACER_H
#define SUPERSPACER_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class SuperSpacer : public Ship
{
private:
	int thrust;
  bool scope;
public:
  	/***********************************************
  	* Constructors.
  	***********************************************/
  	SuperSpacer()
    {
      scope = false;
     	type = 10;
    	rotation = 0;
      point.setX(0);
      point.setY(0);
      alive = true;
      flip = true;
    }
  
 	/***********************************************
  * Apply meathods: These meathods call the mutators for the velocity variable. 
  ***********************************************/
  void up()       { velocity.addDY(-2 * sin((rotation - 90) / 57.2958)); velocity.addDX(-2 * cos((rotation - 90) / 57.2958)); thrust = 1; };
  void down()     
  { 
    if (velocity.getDX() < -0.5) 
      velocity.addDX(1); 
    else if (velocity.getDX() > 0.5)
      velocity.addDX(-1);
    if (velocity.getDY() < -0.5)
      velocity.addDY(1); 
    else if (velocity.getDY() > 0.5)
      velocity.addDY(-1); 
    if (velocity.getDX() >= 1 && velocity.getDX() <= -1)
      velocity.setDX(0);
    if (velocity.getDY() >= 1 && velocity.getDY() <= -1)
      velocity.setDY(0);

  };
  void left()     
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
        rotation -= 12.0;
      else
        rotation += 12.0;
    }
    scope = false;
  };
  void right()    
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
        rotation += 12.0;
      else
        rotation -= 12.0;
    }
    scope = false;

  }; 
  void constant() { thrust = 0;};
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawSuper(point, rotation, thrust, scope); };
  void activateScope() { scope = true; };


};

#endif