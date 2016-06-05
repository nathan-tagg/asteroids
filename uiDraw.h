/***********************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include "point.h"    // Where things are drawn
using std::string;

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *************************************************************************/
void drawDigit(const Point & topLeft, const char & digit);

/*************************************************************************
 * DRAW NUMBER
 * Display an integer on the screen using the 7-segment method
 *************************************************************************/
void drawNumber(const Point & topLeft, unsigned short & number);

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 ************************************************************************/
void drawText(const Point & topLeft, const char * text);

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *************************************************************************/
void rotate(Point & point, const Point & origin, const short & rotation = 0);

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *************************************************************************/
void drawCircle(const Point & center, const short & radius);

/************************************************************************
 * DRAW POLYGON
 * Draw a polygon from a given location (center) of a given size (radius).
 *************************************************************************/
void drawPolygon(const Point & center,
                 const short & radius = 20,
                 const short & points = 4,
                 const short & rotation = 0);
void drawBolt   (const Point & center,
                 const short & radius = 20,
                 const short & points = 4,
                 const short & rotation = 0);

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Point & begin, const Point & end, const float & red = 1.0, const float & green = 1.0, const float & blue = 1.0);

/***********************************************************************
 * DRAW Lander
 * Draw a moon-lander spaceship on the screen at a given point
 ***********************************************************************/
void drawLander   (const Point & point);
void drawRedLander(const Point & point);

/***********************************************************************
 * DRAW Lander Flame
 * Draw the flames coming out of a moonlander for thrust
 ***********************************************************************/
void drawLanderFlames(const Point & point, 
                      const bool & bottom,
                      const bool & left,
                      const bool & right);

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *************************************************************************/
void drawRedDot  (const Point & point);
void drawDot     (const Point & point);
void drawGreenDot(const Point & point);
void drawRound   (const Point & point, const short & rotation);

/************************************************************************
 * DRAW Sacred Bird
 * Draw the bird on the screen
 *************************************************************************/
void drawSacredBird(const Point & center, const float & radius);

/************************************************************************
 * DRAW Tough Bird
 * Draw a tough bird on the screen
 *************************************************************************/
void drawBoom    (const Point & center, const float & radius);
void drawTeleport(const Point & center, const float & radius);

/************************************************************************      
 * DRAW Ship                                                                   
 * Draw the spaceship on the screen                                         
 *************************************************************************/
void drawShip     (const Point & point, const short & rotation, const short & thrust = 1);
void drawSniper   (const Point & point, const short & rotation, const short & thrust = 1, const bool & scope = false);
void drawTank     (const Point & point, const short & rotation, const short & thrust = 1);
void drawOldShip  (const Point & point, const short & rotation, const short & thrust = 1);
void drawSuper    (const Point & point, const short & rotation, const short & thrust = 1, const bool & scope = false);
void drawHarbinger(const Point & point, const short & rotation, const short & thrust = 1);
void drawUFO	  (const Point & point, const short & rotation);

/**********************************************************************
 * DRAW * ASTEROID
 **********************************************************************/
void drawSmallAsteroid   (const Point & point, const short & rotation, const short & r, const short & g, const short & b);
void drawMediumAsteroid  (const Point & point, const short & rotation, const short & r, const short & g, const short & b);
void drawLargeAsteroid   (const Point & point, const short & rotation, const short & r, const short & g, const short & b);
void drawHugeAsteroid    (const Point & point, const short & rotation, const short & r, const short & g, const short & b);
void drawBehemothAsteroid(const Point & point, const short & rotation, const short & r, const short & g, const short & b);

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int  random(const int  & min, const int  & max);
double random(const double & min, const double & max);


#endif // UI_DRAW_H
