#ifndef LANDER_H
#define LANDER_H

#include "uiDraw.h"
#include "ship.h"

class Lander : public Ship
{
private:
public:  
  /***********************************************
  * Constructors.
  ***********************************************/
   Lander()
   {
      type = 2;
      point.setX(0);
      point.setY(0);
      alive = true;
      rotation = 0;
      flip = true;
   }
   /***********************************************
   * Apply meathods: These meathods call the mutators for the velocity variable. 
   ***********************************************/
   virtual void down()     { velocity.addDY(.15); drawLanderFlames(point, 1, 0, 0); };
   virtual void left()     { velocity.addDX(.1);  drawLanderFlames(point, 0, 1, 0); };
   virtual void right()    { velocity.addDX(-.1); drawLanderFlames(point, 0, 0, 1); };
   virtual void up()       {                                                        };
   virtual void constant() { velocity.addDY(-.0525); };  
   /*********************************************
   * Draw: This meathod will draw the lander in the environment.
   *********************************************/
   virtual void draw() { drawLander(point); };

};

#endif
