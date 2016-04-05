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
void drawDigit(const Point & topLeft, char digit);

/*************************************************************************
 * DRAW NUMBER
 * Display an integer on the screen using the 7-segment method
 *************************************************************************/
void drawNumber(const Point & topLeft, int number);

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
void rotate(Point & point, const Point & origin, int rotation = 0);

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 * measured in degrees (0 - 360)
 *************************************************************************/
void drawRect(const Point & center, int width, int height, int rotation);

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *************************************************************************/
void drawCircle(const Point & center, int radius);

/************************************************************************
 * DRAW POLYGON
 * Draw a polygon from a given location (center) of a given size (radius).
 *************************************************************************/
void drawPolygon(const Point & center,
                 int radius = 20,
                 int points = 4,
                 int rotation = 0);
void drawBolt(const Point & center,
                 int radius = 20,
                 int points = 4,
                 int rotation = 0);

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Point & begin, const Point & end,
             float red = 1.0, float green = 1.0, float blue = 1.0);


/***********************************************************************
 * DRAW Lander
 * Draw a moon-lander spaceship on the screen at a given point
 ***********************************************************************/
void drawLander(const Point & point);
void drawRedLander(const Point & point);

/***********************************************************************
 * DRAW Lander Flame
 * Draw the flames coming out of a moonlander for thrust
 ***********************************************************************/
void drawLanderFlames(const Point & point, 
                      bool bottom,
                      bool left,
                      bool right);

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *************************************************************************/
void drawRedDot(const Point & point);
void drawDot(const Point & point);
void drawRound(const Point & point, int rotation);

/************************************************************************
 * DRAW Sacred Bird
 * Draw the bird on the screen
 *************************************************************************/
void drawSacredBird(const Point & center, float radius);

/************************************************************************
 * DRAW Tough Bird
 * Draw a tough bird on the screen
 *************************************************************************/
void drawToughBird(const Point & center, float radius);
void drawTeleport(const Point & center, float radius);

/************************************************************************      
 * DRAW Ship                                                                   
 * Draw the spaceship on the screen                                         
 *************************************************************************/
void drawShip(const Point & point, int rotation, int thrust = 1);
void drawSniper(const Point & point, int rotation, int thrust = 1, bool scope = false);
void drawTank(const Point & point, int rotation, int thrust = 1);
void drawSuper(const Point & point, int rotation, int thrust = 1, bool scope = false);
void drawOldShip(const Point & point, int rotation, int thrust = 1);

/**********************************************************************
 * DRAW * ASTEROID
 **********************************************************************/
void drawSmallAsteroid(   const Point & point, int rotation, int r, int g, int b);
void drawMediumAsteroid(  const Point & point, int rotation, int r, int g, int b);
void drawLargeAsteroid(   const Point & point, int rotation, int r, int g, int b);
void drawHugeAsteroid(    const Point & point, int rotation, int r, int g, int b, int cracks);
void drawBehemothAsteroid(const Point & point, int rotation, int r, int g, int b);

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);


#endif // UI_DRAW_H
