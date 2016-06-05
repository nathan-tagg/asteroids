#ifndef SUPERSPACER_H
#define SUPERSPACER_H

#include <math.h>

#include "uiDraw.h"
#include "ship.h"

class SuperSpacer : public Ship
{
private:
	bool thrust;
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
  void up()       { velocity.addDY(-.8 * sin((rotation - 90) / 57.2958)); velocity.addDX(-.8 * cos((rotation - 90) / 57.2958)); thrust = true; };
  void down()     
  { 
    if (velocity.getDX() < -0.4) 
      velocity.addDX(.4); 
    else if (velocity.getDX() > 0.4)
      velocity.addDX(-.4);
    if (velocity.getDY() < -0.4)
      velocity.addDY(.4); 
    else if (velocity.getDY() > 0.4)
      velocity.addDY(-.4); 
    if (velocity.getDX() <= .4 && velocity.getDX() >= -.4)
      velocity.setDX(0);
    if (velocity.getDY() <= .4 && velocity.getDY() >= -.4)
      velocity.setDY(0);

  };
  void left()     
  {
    if (scope)
    { 
      if ( flip )
        rotation -= 0.5;
      else
        rotation += 0.5;
    }
    else
    {
      if ( flip )
        rotation -= 5.0;
      else
        rotation += 5.0;
    }
    scope = false;
  };
  void right()    
  {
    if (scope)
    { 
      if ( flip )
        rotation += 0.5;
      else
        rotation -= 0.5;
    }
    else
    {
      if ( flip )
        rotation += 5.0;
      else
        rotation -= 5.0;
    }
    scope = false;

  }; 
  void constant() { thrust = false;};
  
 	/*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  virtual void draw() { drawSuper(point, rotation, thrust, scope); };
  void activateScope() { scope = true; };


};

#endif