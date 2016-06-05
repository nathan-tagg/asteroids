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

using namespace std;
#define NUM 25

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br) : topLeft(tl), bottomRight(br)
{
   createRocks(NUM);
   ship = &spacer;
   score = 0;
   distance = 300;
   A = 0;
   S = 0;
   level = 1;
   clock = 0;
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
void Game :: createRocks(short num)
{
   for (int i = 0; i < num; i++)
   {
      Rock * rock = new LargeRock;
      Point start;
      if (random(1, 5) % 2)
      {
         Point p(random(-699, 699), 499);
         start = p;
      }
      else
      {
         Point p(699, random(-499, 499));
         start = p;
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
      short shipSize;
      if (ship->getType() == 6)
         shipSize = 3;
      else
         shipSize = 10;
      if ((ship->getPoint() - (*itr)->getPoint()) < ((*itr)->getSize() + shipSize) && (*itr)->isAlive() && !(*itr)->isImmortal())
      {
         drawBoom(ship->getPoint(), 50);
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
      if ((*it)->getType() == 12)
      {
         if ((*it)->getLife() == 990)
            (*it)->stop();
         short proximo = 300;
         for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
         {
            short closer = (*it)->getPoint() - (*itr)->getPoint();
            if (closer < proximo)
            {
               proximo = closer;
               closest = (*itr);
            }
            if (proximo < 300)
            {
               float angle = atan2(closest->getPoint().getY() - (*it)->getPoint().getY(), closest->getPoint().getX() - (*it)->getPoint().getX());
               (*it)->setVelocity(cos(angle) * 4, sin(angle) * 4);
               if (proximo < 50)
                  (*it)->setVelocity(closest->getVelocity());
            }
            
         }
         if (proximo < 100 && random(-20, 20) == 0)
         {
            float angle = atan2(closest->getPoint().getY() - (*it)->getPoint().getY(), closest->getPoint().getX() - (*it)->getPoint().getX());
            Bullet * newBullet = new Bullet;
            newBullet->setPoint((*it)->getPoint());
            newBullet->setVelocity((*it)->getVelocity());
            newBullet->fire(4, angle * 57.2958 + 270);
            bullets.push_back(newBullet);
         }
      }
      if ((*it)->getType() == 8)
      {
         if ((*it)->getLife() == 9990)
            (*it)->stop();
         short perto = 500;
         for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
         {
            short close = (*it)->getPoint() - (*itr)->getPoint();
            if (close < perto)
            {
               perto = close;
               closest = (*itr);
            }
            if ((*itr)->getPoint() - ship->getPoint() < 200)
            {
               closest = (*itr);
            }
            if ((*it)->getLife() < 9900 && closest != NULL)
            {
               float angle = atan2(closest->getPoint().getY() - (*it)->getPoint().getY(), closest->getPoint().getX() - (*it)->getPoint().getX());
               (*it)->setVelocity(cos(angle) * 10, sin(angle) * 10);
               if (perto < 100)
                  (*it)->setVelocity(closest->getVelocity());
            } 
         }
         if (perto < 100 && clock % 5 == 0)
         {
            float angle = atan2(closest->getPoint().getY() - (*it)->getPoint().getY(), closest->getPoint().getX() - (*it)->getPoint().getX());
            Bullet * newBullet = new Bullet;
            newBullet->setPoint((*it)->getPoint());
            newBullet->setVelocity((*it)->getVelocity());
            newBullet->fire(4, angle * 57.2958 + 270);
            bullets.push_back(newBullet);
         }
      }
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
            if ((*itr)->getSize() == 18 && (*it)->getType() != 9)
            {
               Rock * rockOne = new MediumRock;
               rockOne->setVelocity((*itr)->getVelocity());
               rockOne->addVelocity(0 , .25);
               rockOne->setPoint((*itr)->getPoint());
               Rock * rockTwo = new MediumRock;
               rockTwo->setVelocity((*itr)->getVelocity());
               rockTwo->addVelocity(0 , -.25);
               rockTwo->setPoint((*itr)->getPoint());
               Rock * rockThree = new SmallRock;
               rockThree->setVelocity((*itr)->getVelocity());
               rockThree->addVelocity(.25 ,0);
               rockThree->setPoint((*itr)->getPoint());
               rocks.push_back(rockOne);
               rocks.push_back(rockTwo);
               rocks.push_back(rockThree);
            }
            if ((*itr)->getSize() == 13 && (*it)->getType() != 9)
            {
               Rock * rockOne = new SmallRock;
               rockOne->setVelocity((*itr)->getVelocity());
               rockOne->addVelocity(1, 0);
               rockOne->setPoint((*itr)->getPoint());
               Rock * rockTwo = new SmallRock;
               rockTwo->setVelocity((*itr)->getVelocity());
               rockTwo->addVelocity(-1, 0);
               rockTwo->setPoint((*itr)->getPoint());
               rocks.push_back(rockOne);
               rocks.push_back(rockTwo);
            }
            score += 10;
            (*it)->kill();
            if ((*it)->getType() != 9)
               (*itr)->kill();
            else
            {
               Velocity vel(0, 0);
               (*itr)->setVelocity(vel);
            }
            drawBoom((*it)->getPoint(), 7);
         }
      }
   }
}

void Game :: seek()
{
   for (list<Bullet*> :: iterator it = bullets.begin(); it != bullets.end(); ++it)
   {    
      if ((*it)->getType() == 7)
      {
         short cumprimento = 100;
         for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
         {
            short farness = (*it)->getPoint() - (*itr)->getPoint();
            if (farness < cumprimento && !(*itr)->isImmortal() && (*it)->getLife() < 90)
            {
               cumprimento = farness;
               closest = (*itr);
            }
         }
         if (cumprimento < 100)
         {
            float angle = atan2(closest->getPoint().getY() - (*it)->getPoint().getY(), closest->getPoint().getX() - (*it)->getPoint().getX());
            (*it)->setVelocity(cos(angle) * 10 + random(-1.0, 1.0), sin(angle) * 10 + random (-1.0, 1.0));
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
   if (numRocks == 0)
   {
      createRocks(score / 80);
   }
   Point scorePoint(topLeft.getX() + 20, topLeft.getY() - 20);
   drawNumber(scorePoint, score);
   clock++;
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
   
   if (ui.isSpace())
   {
       Bullet * newBullet = new Bullet;
       newBullet->setPoint(ship->getPoint());
       if (ship->getType() != 3)
          newBullet->setVelocity(ship->getVelocity());
       newBullet->fire(ship->getType(), ship->getRotation());
       bullets.push_back(newBullet);
       if (ship->getType() != 8 && S)
       {
         Velocity v = ship->getVelocity();
         Point p = ship->getPoint();
         harbinger.setRotation(ship->getRotation());
         ship = &harbinger;
         ship->setPoint(p);
         ship->setVelocity(v);
      }
   }

   if (ui.isRapid() && ship->getType() == 4 || ship->getType() == 10 && ui.isRapid() || ui.isRapid() && ship->getType() == 7)
   {
      Bullet * newBullet = new Bullet;
      if (ship->getType() != 7)
         newBullet->setPoint(ship->getPoint());
      else
      {
         Point rightCannon(ship->getPoint().getX() + 7, ship->getPoint().getY() + 7);
         rotate(rightCannon, ship->getPoint(), ship->getRotation());
         Point leftCannon(ship->getPoint().getX() - 7, ship->getPoint().getY() + 7);
         rotate(leftCannon, ship->getPoint(), ship->getRotation());
         if (random(1, 10) % 2 == 0)
            newBullet->setPoint(rightCannon);
         else
            newBullet->setPoint(leftCannon);
      }
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
      if (ship->getType() == 3 || ship->getType() == 10 || ship->getType() == 6)
      {
         for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
         {
            if (ship->getType() == 10 && !(*itr)->isImmortal() || ship->getType() == 3 || ship->getType() == 6)
            {
               short distancia = (ship->getPoint() - (*itr)->getPoint());
               if (distancia < distance)
               {
                  distance = distancia;
                  closest = (*itr);
               }
            }
         }
         if (distance < 300 && ship->getType() != 6 && closest != NULL)
         {
            short delay;
            if (ship->getType() == 3)
            {
               delay = 9;
            }
            else
            {
               delay = 9;
            }
            if (ship->getPoint().getX() - closest->getPoint().getX() >= 0)
               ship->setRotation(90 +  (57.2958 * atan((ship->getPoint().getY() - closest->getPoint().getY() - (distance  / delay) * closest->getVelocity().getDY()) / (ship->getPoint().getX() - closest->getPoint().getX() - (distance / delay) * closest->getVelocity().getDX()))));
            else
               ship->setRotation(270 + (57.2958 * atan((ship->getPoint().getY() - closest->getPoint().getY() - (distance  / delay) * closest->getVelocity().getDY()) / (ship->getPoint().getX() - closest->getPoint().getX() - (distance / delay) * closest->getVelocity().getDX()))));
         }
         if (distance < 300 && ship->getType() == 6 && closest != NULL)
         {
            float angle = atan2(closest->getPoint().getY() - ship->getPoint().getY(), closest->getPoint().getX() - ship->getPoint().getX());
            ship->setRotation(57.2958 * angle + 90);
            ship->up();
         }
         distance = 300;
      }
      seek();
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
      harbinger.invert();
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
            drawBoom(ship->getPoint(), 15);
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
         {
            if (teleport - (*itr)->getPoint() < ((*itr)->getSize() + 30) && (*itr)->isAlive())
            {
               safe = false;
            }
         }
         if (safe)
         {
            drawTeleport(ship->getPoint(), 15);
            Velocity v(0, 0);
            ship->setPoint(teleport);
            ship->setVelocity(v);   
         }
         else
            drawBoom(ship->getPoint(), 15);
      }
   }
   if (ui.isA())
   {
      if (ship->getType() == 7)
      {
         short proximidade = 600;
         for (list<Rock*> :: iterator itr = rocks.begin(); itr != rocks.end(); ++itr)
         {
            if (!(*itr)->isImmortal() && (*itr)->getVelocity().getDX() || (*itr)->getVelocity().getDY())
            {
               short distancia = (ship->getPoint() - (*itr)->getPoint());
               if (distancia < proximidade)
               {
                  proximidade = distancia;
                  closest = (*itr);
               }
            }
         }
         if (ship->getPoint().getX() - closest->getPoint().getX() >= 0)
            ship->setRotation(90 +  (57.2958 * atan((ship->getPoint().getY() - closest->getPoint().getY() - (proximidade  / 10) * closest->getVelocity().getDY()) / (ship->getPoint().getX() - closest->getPoint().getX() - (proximidade / 10) * closest->getVelocity().getDX()))));
         else
            ship->setRotation(270 + (57.2958 * atan((ship->getPoint().getY() - closest->getPoint().getY() - (proximidade  / 10) * closest->getVelocity().getDY()) / (ship->getPoint().getX() - closest->getPoint().getX() - (proximidade / 10) * closest->getVelocity().getDX()))));
         Bullet * newBullet = new Bullet;
         newBullet->setPoint(ship->getPoint());
         newBullet->fire(9, ship->getRotation());
         bullets.push_back(newBullet);
      }
      else
      {
         A = 40;
      }      
   }
   if (ui.isS())
   {
      if (ship->getType() == 7 && helpers())
      {
         Bullet * newBullet = new Bullet;
         newBullet->setPoint(ship->getPoint());
         newBullet->fire(8, ship->getRotation());
         bullets.push_back(newBullet);
      }
      if (A)
      {
         S = 40;
      }
   }
   if (ui.isZ())
   {
      if (ship->getType() != 11)
      {
         ufo.setPoint(ship->getPoint());
         ship = &ufo;
      }
      else
      {
         if (ship->getType() == 11 && helpers())
         {
            Bullet * newBullet = new Bullet;
            newBullet->setPoint(ship->getPoint());
            newBullet->fire(12, ship->getRotation());
            bullets.push_back(newBullet);
         }
      }
   }
   if (A > 0)
      A--;
   if (S > 0)
      S--;
}

bool Game :: helpers()
{
   short lilDudes = 0;
   for (list<Bullet*> :: iterator it = bullets.begin(); it != bullets.end(); ++it)
   {
      if ((*it)->getType() == 8 && ship->getType() == 7)
         lilDudes++;
      if ((*it)->getType() == 12 && ship->getType() == 11)
         lilDudes++;
   }
   if (ship->getType() == 7)
      return (lilDudes < 1);
    else if (ship->getType() == 11)
      return (lilDudes < 10);
    
    return true;
}
