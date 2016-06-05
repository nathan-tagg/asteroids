/*************************************************************
 * Header File: GAME
 * Author: Nathan Tagg
 *************************************************************/

#ifndef GAME_H
#define GAME_H

#include <list>
#include <string>

#include "bullet.h"
#include "rock.h"
#include "hugeRock.h"
#include "largeRock.h"
#include "mediumRock.h"
#include "smallRock.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "superSpacer.h"
#include "lander.h"
#include "spacer.h"
#include "sniper.h"
#include "tank.h"
#include "ship.h"
#include "oldy.h"
#include "harbinger.h"
#include "ufo.h"
//#include <irrklang/irrKlang.h>

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   ~Game();
   
   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);
   
   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   void createRocks(short num);
   void advanceRocks();
   void advanceBullets();
   void advanceShip();
   void collisions();
   void seek();
   void displayInfo();
   bool helpers();
   
private:
   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;   
   unsigned short score;
   unsigned short level;
   unsigned short clock;
   short distance;
   short numRocks;
   short A;
   short S;

   //ISoundEngine *SoundEngine;
   Rock * closest;
   Ship * ship;
   Lander lander;
   Spacer spacer;
   Sniper sniper;
   SuperSpacer super;
   Tank tank;
   Oldy oldy;
   Harbinger harbinger;
   Ufo ufo;
   std::list<Bullet*> bullets;
   std::list<Rock*> rocks;
   string code;
};

#endif /* GAME_H */
