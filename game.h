/*************************************************************
 * File: game.h
 * Author: Br. Burton
 *
 * Description: The game of Skeet. This class holds each piece
 *  of the game (birds, bullets, rifle, score). It also has
 *  methods that make the game happen (advance, interact, etc.)
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
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
   void createRocks(int num);
   void advanceRocks();
   void advanceBullets();
   void advanceShip();
   void collisions();
   void displayInfo();
   
private:
   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;   
   int score;
   int distance;
   int numRocks;

   //ISoundEngine *SoundEngine;
   Rock * closest;
   Ship * ship;
   Lander lander;
   Spacer spacer;
   Sniper sniper;
   SuperSpacer super;
   Tank tank;
   Oldy oldy;
   std::list<Bullet*> bullets;
   std::list<Rock*> rocks;
   string code;
};

#endif /* GAME_H */
