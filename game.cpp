/*************************************************************
 * File: game.cpp
 * Author: Nathan Tagg
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include "game.h"

#include <list>
#include <iostream>
#include <math.h>
//#include <irrklang/irrKlang.h>

using namespace std;
#define NUM 10

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br) : topLeft(tl), bottomRight(br)
{
   createRocks(NUM);
   ship = &spacer;
   score = 0;
   distance = 300;
   //*SoundEngine = createIrrKlangDevice();
   //SoundEngine->play2D("audio/breakout.mp3", GL_TRUE);
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   for (list<Rock*> :: iterator it = rocks.begin(); it != rocks.end();)
   {
      delete * it;
      it = rocks.erase(it);
   }
}

/***************************************
* Create Rocks
***************************************/
void Game :: createRocks(int num)
{
   for (int i = 0; i < num; i++)
   {
      Rock * rock = new LargeRock;
      Point start;
      if (random(1, 5) == 1)
      {
         Point p(random(-650, 650), 400);
         start.setX(p.getX());
         start.setY(p.getY());
      }
      if (random(1, 5) == 2)
      {
         Point p(650, random(-400, 400));
         start.setX(p.getX());
         start.setY(p.getY());
      }
      if (random(1, 5) == 3)
      {
         Point p(random(-650, 650), -400);
         start.setX(p.getX());
         start.setY(p.getY());
      }
      if (random(1, 5) <= 4)
      {
         Point p(-650, random(-400, 400));
         start.setX(p.getX());
         start.setY(p.getY());
      }
      rock->setPoint(start);
      rocks.push_back(rock);     
   }
}

/************************************
* advance meathods
************************************/
void Game :: advanceShip()
{
   ship->advance();
   for(list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
   {
      int shipSize;
      if (ship->getType() == 6)
         shipSize = 3;
      else
         shipSize = 10;
      if ((ship->getPoint() - (*itr)->getPoint()) < ((*itr)->getSize() + shipSize) && (*itr)->isAlive() && !(*itr)->isImmortal())
      {
         drawToughBird(ship->getPoint(), 50);
         for (list<Rock*> :: iterator it = rocks.begin(); it != rocks.end(); ++it)
         {
            (*it)->kill();
         }
         ship->reset();
         spacer.setRotation(0);
         sniper.setRotation(0);
         score = 0;
         createRocks(NUM);
      } 
   }   
}

void Game :: advanceBullets()
{
   for(list<Bullet*> :: iterator it = bullets.begin(); it != bullets.end(); ++it)
   {
      if ((*it)->isAlive())
         (*it)->advance();
      else
      {
         delete * it;
         it = bullets.erase(it);
      }
   }
}

void Game :: advanceRocks()
{
   for(list<Rock*> :: iterator it = rocks.begin(); it != rocks.end(); ++it)
   {
      if ((*it)->isAlive())
         (*it)->advance();
      else
      {
         delete * it;
         it = rocks.erase(it);
      }
   }
}

void Game :: collisions()
{
   for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
   {    
      for (list<Bullet*> :: iterator it = bullets.begin(); it != bullets.end(); ++it)
      {
         if ((*it)->getPoint() - (*itr)->getPoint() < (*itr)->getSize() && (*itr)->isAlive() && !(*itr)->isImmortal())
         {
            if ((*itr)->getSize() == 18)
            {
               Rock * rockOne = new MediumRock;
               rockOne->setVelocity((*itr)->getVelocity());
               rockOne->addVelocity(0 ,1);
               rockOne->setPoint((*itr)->getPoint());
               Rock * rockTwo = new MediumRock;
               rockTwo->setVelocity((*itr)->getVelocity());
               rockTwo->addVelocity(0 ,-1);
               rockTwo->setPoint((*itr)->getPoint());
               Rock * rockThree = new SmallRock;
               rockThree->setVelocity((*itr)->getVelocity());
               rockThree->addVelocity(1 ,0);
               rockThree->setPoint((*itr)->getPoint());
               rocks.push_back(rockOne);
               rocks.push_back(rockTwo);
               rocks.push_back(rockThree);
            }
            if ((*itr)->getSize() == 13)
            {
               Rock * rockOne = new SmallRock;
               rockOne->setVelocity((*itr)->getVelocity());
               rockOne->addVelocity(3, 0);
               rockOne->setPoint((*itr)->getPoint());
               Rock * rockTwo = new SmallRock;
               rockTwo->setVelocity((*itr)->getVelocity());
               rockTwo->addVelocity(-3, 0);
               rockTwo->setPoint((*itr)->getPoint());
               rocks.push_back(rockOne);
               rocks.push_back(rockTwo);
            }
            score += 10;
            (*it)->kill();
            (*itr)->kill();
            drawToughBird((*it)->getPoint(), 7);
         }
      }
   }
}

void Game :: advance()
{
   advanceShip();
   advanceBullets();
   advanceRocks();
   collisions();
   numRocks = 0;
   for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
   {
      numRocks++;
   }
   if (50 < (score / numRocks) && numRocks < 100)
   {
      createRocks(1);
   }
   Point scorePoint(topLeft.getX() + 20, topLeft.getY() - 20);
   drawNumber(scorePoint, score);
}

/************************************
* Handle input
************************************/
void Game :: handleInput(const Interface & ui)
{
   if (ui.isLeft())
   {
      ship->left();
   }
   
   if (ui.isRight())
   {
      ship->right();
   }
   
   if (ui.isSpace() && ship->getType() != 4 && ship->getType() != 10)
   {
       Bullet * newBullet = new Bullet;
       newBullet->setPoint(ship->getPoint());
       if (ship->getType() != 3)
          newBullet->setVelocity(ship->getVelocity());
       newBullet->fire(ship->getType(), ship->getRotation());
       bullets.push_back(newBullet);
   }

   if (ui.isRapid() && ship->getType() == 4 || ship->getType() == 10 && ui.isRapid())
   {
      Bullet * newBullet = new Bullet;
      newBullet->setPoint(ship->getPoint());
      if (ship->getType() != 10)
         newBullet->setVelocity(ship->getVelocity());
      newBullet->fire(ship->getType(), ship->getRotation());
      bullets.push_back(newBullet);
      if (ship->getType() == 10)
      {
         super.activateScope();
      }
   }

   if (ui.isDown())
   {
      ship->down();
      if (ship->getType() == 3 || ship->getType() == 10)
      {
         for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
         {
            int distancia = (ship->getPoint() - (*itr)->getPoint());
            if (distancia < distance)
            {
               distance = distancia;
               closest = (*itr);
            }
         }
         if (distance < 300)
         {
            int delay;
            if (ship->getType() == 3)
            {
               delay = 25;
            }
            else
            {
               delay = 10;
            }
            if (ship->getPoint().getX() - closest->getPoint().getX() >= 0)
               ship->setRotation(90 +  (57.2958 * atan((ship->getPoint().getY() - closest->getPoint().getY() - (distance  / delay) * closest->getVelocity().getDY()) / (ship->getPoint().getX() - closest->getPoint().getX() - (distance / delay) * closest->getVelocity().getDX()))));
            else
               ship->setRotation(270 + (57.2958 * atan((ship->getPoint().getY() - closest->getPoint().getY() - (distance  / delay) * closest->getVelocity().getDY()) / (ship->getPoint().getX() - closest->getPoint().getX() - (distance / delay) * closest->getVelocity().getDX()))));
         }
         distance = 300;
      }
   }

   if (ui.isUp())
   {
      ship->up();
   }
   if (ui.isX())
   {
      spacer.invert();
      sniper.invert();
      tank.invert();
      oldy.invert();
      super.invert();
   }

   if (ui.isC())
   {
   	if (ship->getType() != 2)
   	{
      	Velocity v = ship->getVelocity();
      	Point p = ship->getPoint();
      	ship = &lander;
      	ship->setPoint(p);
      	ship->setVelocity(v);
      }
      else
      {
         Velocity v(0, 0);
      	drawRedLander(ship->getPoint());
         Bullet * newBullet = new Bullet;
         newBullet->setPoint(ship->getPoint());
         newBullet->setVelocity(v);
         newBullet->fire(5, ship->getRotation());
         bullets.push_back(newBullet);
      }
   }
   if (ui.isV())
   {
   	if (ship->getType() != 1)
   	{
   	   Velocity v = ship->getVelocity();
         Point p = ship->getPoint();
         spacer.setRotation(ship->getRotation());
         ship = &spacer;
         ship->setPoint(p);
         ship->setVelocity(v);
      }
      else
      {
         bool safe = true;
         Point teleport(random (-600, 600), random(-400, 400));
         for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
         if (teleport - (*itr)->getPoint() < ((*itr)->getSize() + 30) && (*itr)->isAlive())
         {
            safe = false;
         }
         if (safe)
         {
            drawTeleport(ship->getPoint(), 15);
            Velocity v(0, 0);
            ship->setPoint(teleport);
            ship->setVelocity(v);	
         }
         else
            drawToughBird(ship->getPoint(), 15);
         spacer.setRotation(0);
      }
   }
   if (ui.isB())
   {
      if (ship->getType() != 3)
      {
         Velocity v = ship->getVelocity();
         Point p = ship->getPoint();
         sniper.setRotation(ship->getRotation());
         ship = &sniper;
         ship->setPoint(p);
         ship->setVelocity(v);
      }
      else
         sniper.activateScope();
   }
   if (ui.isN())
   {
      if (ship->getType() != 4)
      {
         Velocity v = ship->getVelocity();
         Point p = ship->getPoint();
         tank.setRotation(ship->getRotation());
         ship = &tank;
         ship->setPoint(p);
         ship->setVelocity(v);
      }
   }
   if (ui.isM())
   {
      if (ship->getType() != 6)
      {
         Velocity v = ship->getVelocity();
         Point p = ship->getPoint();
         oldy.setRotation(ship->getRotation());
         ship = &oldy;
         ship->setPoint(p);
         ship->setVelocity(v);
      }
      else
         ship->setRotation(0);
   }
   if (ui.isI())
   {
   }
   if (ui.isT())
   {
      if (ship->getType() != 10 && oldy.ultimateDestruction() && ship->getType() == 6)
      {
         Velocity v = ship->getVelocity();
         Point p = ship->getPoint();
         super.setRotation(ship->getRotation());
         ship = &super;
         ship->setPoint(p);
         ship->setVelocity(v);
      }
      else if (ship->getType() == 10)
      {
         Velocity v(0, 0);
         drawShip(ship->getPoint(), ship->getRotation(), 0);
         Bullet * newBullet = new Bullet;
         newBullet->setPoint(ship->getPoint());
         newBullet->setVelocity(v);
         newBullet->fire(5, ship->getRotation());
         bullets.push_back(newBullet);
         bool safe = true;
         Point teleport(random (-600, 600), random(-400, 400));
         for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
         if (teleport - (*itr)->getPoint() < ((*itr)->getSize() + 30) && (*itr)->isAlive())
         {
            safe = false;
         }
         if (safe)
         {
            drawTeleport(ship->getPoint(), 15);
            Velocity v(0, 0);
            ship->setPoint(teleport);
            ship->setVelocity(v);   
         }
         else
            drawToughBird(ship->getPoint(), 15);
      }
   }
}
