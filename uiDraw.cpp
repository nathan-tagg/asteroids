/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock


#ifdef __APPLE__
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "point.h"
#include "uiDraw.h"
#include <vector>

using namespace std;

#define deg2rad(value) ((M_PI / 180) * (value))

/*********************************************
 * NUMBER OUTLINES
 * We are drawing the text for score and things
 * like that by hand to make it look "old school."
 * These are how we render each individual charactger.
 * Note how -1 indicates "done".  These are paired
 * coordinates where the even are the x and the odd
 * are the y and every 2 pairs represents a point
 ********************************************/
const char NUMBER_OUTLINES[10][20] =
{
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
  {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
  {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
  {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
  {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
  {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
  {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
  {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
  {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawDigit(const Point & topLeft, char digit)
{
   // we better be only drawing digits
   assert(isdigit(digit));
   if (!isdigit(digit))
      return;

   // compute the row as specified by the digit
   int r = digit - '0';
   assert(r >= 0 && r <= 9);

   // go through each segment.
   for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
   {
      assert(NUMBER_OUTLINES[r][c    ] != -1 &&
             NUMBER_OUTLINES[r][c + 1] != -1 &&
             NUMBER_OUTLINES[r][c + 2] != -1 &&
             NUMBER_OUTLINES[r][c + 3] != -1);

      //Draw a line based off of the num structure for each number
      Point start;
      start.setX(topLeft.getX() + NUMBER_OUTLINES[r][c]);
      start.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 1]);
      Point end;
      end.setX(topLeft.getX() + NUMBER_OUTLINES[r][c + 2]);
      end.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 3]);
         
      drawLine(start, end);
   }
}

/*************************************************************************
 * DRAW NUMBER
 * Display an integer on the screen using the 7-segment method
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawNumber(const Point & topLeft, int number)
{
   // our cursor, if you will. It will advance as we output digits
   Point point = topLeft;
   
   // is this negative
   bool isNegative = (number < 0);
   number *= (isNegative ? -1 : 1);
   
   // render the number as text
   ostringstream sout;
   sout << number;
   string text = sout.str();

   // handle the negative
   if (isNegative)
   {
      glBegin(GL_LINES);
      glVertex2f(point.getX() + 1, point.getY() - 5);
      glVertex2f(point.getX() + 5, point.getY() - 5);
      glEnd();
      point.addX(11);
   }
   
   // walk through the text one digit at a time
   for (const char *p = text.c_str(); *p; p++)
   {
      assert(isdigit(*p));
      drawDigit(point, *p);
      point.addX(11);
   }
}


/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Point & topLeft, const char * text)
{
   void *pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18

   // prepare to draw the text from the top-left corner
   glRasterPos2f(topLeft.getX(), topLeft.getY());

   // loop through the text
   for (const char *p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

/************************************************************************
 * DRAW POLYGON
 * Draw a POLYGON from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the polygon
 *          radius   Size of the polygon
 *          points   How many points will we draw it.  Larger the number,
 *                   the more line segments we will use
 *          rotation True circles are rotation independent.  However, if you
 *                   are drawing a 3-sided polygon (triangle), this matters!
 *************************************************************************/
void drawPolygon(const Point & center, int radius, int points, int rotation)
{
   // begin drawing
   glBegin(GL_LINE_LOOP);

   //loop around a circle the given number of times drawing a line from
   //one point to the next
   for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / points)
   {
      Point temp(false /*check*/);
      temp.setX(center.getX() + (radius * cos(i)));
      temp.setY(center.getY() + (radius * sin(i)));
      rotate(temp, center, rotation);
      glVertex2f(temp.getX(), temp.getY());
   }

   // complete drawing
   glEnd();

}

void drawBolt(const Point & center, int radius, int points, int rotation)
{
   // begin drawing
   glBegin(GL_LINE_LOOP);
   glColor3f(.7, .2, .2);
   //loop around a circle the given number of times drawing a line from
   //one point to the next
   for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / points)
   {
      Point temp(false /*check*/);
      temp.setX(center.getX() + (radius * cos(i)));
      temp.setY(center.getY() + (radius * sin(i)));
      rotate(temp, center, rotation);
      glVertex2f(temp.getX(), temp.getY());
   }
   glColor3f(1,1,1);
   // complete drawing
   glEnd();

}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  point    The point to be moved
 *           center   The center point we will rotate around
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
void rotate(Point & point, const Point & origin, int rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(deg2rad(rotation));
   double sinA = sin(deg2rad(rotation));

   // remember our original point
   Point tmp(false /*check*/);
   tmp.setX(point.getX() - origin.getX());
   tmp.setY(point.getY() - origin.getY());

   // find the new values
   point.setX(static_cast<int> (tmp.getX() * cosA -
                                tmp.getY() * sinA) +
              origin.getX());
   point.setY(static_cast<int> (tmp.getX() * sinA +
                                tmp.getY() * cosA) +
              origin.getY());
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 *************************************************************************/
void drawLine(const Point & begin, const Point & end,
              float red, float green, float blue)
{
  // Get ready...
  glBegin(GL_LINES);
  glColor3f(red, green, blue);

  // Draw the actual line
  glVertex2f(begin.getX(), begin.getY());
  glVertex2f(  end.getX(),   end.getY());

  // Complete drawing
  glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
  glEnd();
}

/***********************************************************************
 * DRAW Lander
 * Draw a moon-lander spaceship on the screen at a given point
 ***********************************************************************/
void drawLander(const Point & point)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {-6, 0}, {-10,0}, {-8, 0}, {-8, 3},  // left foot
      {-5, 4}, {-5, 7}, {-8, 3}, {-5, 4},  // left leg
      {-1, 4}, {-3, 2}, { 3, 2}, { 1, 4}, {-1, 4}, // bottom
      { 5, 4}, { 5, 7}, {-5, 7}, {-3, 7},  // engine square
      {-6,10}, {-6,13}, {-3,16}, { 3,16},   // left of habitat
      { 6,13}, { 6,10}, { 3, 7}, { 5, 7},   // right of habitat
      { 5, 4}, { 8, 3}, { 5, 7}, { 5, 4},  // right leg
      { 8, 3}, { 8, 0}, {10, 0}, { 6, 0}   // right foot
   };

  // draw it
  glBegin(GL_LINE_STRIP);
  glColor3f(.3, 1, .3);
  for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
       glVertex2f(point.getX() + points[i].x,
                  point.getY() + points[i].y);

   // complete drawing
  glColor3f(1, 1, 1);
  glEnd();
   
   
}


/***********************************************************************
 * DRAW Lander
 * Draw a moon-lander spaceship on the screen at a given point
 ***********************************************************************/
void drawRedLander(const Point & point)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {-6, 0}, {-10,0}, {-8, 0}, {-8, 3},  // left foot
      {-5, 4}, {-5, 7}, {-8, 3}, {-5, 4},  // left leg
      {-1, 4}, {-3, 2}, { 3, 2}, { 1, 4}, {-1, 4}, // bottom
      { 5, 4}, { 5, 7}, {-5, 7}, {-3, 7},  // engine square
      {-6,10}, {-6,13}, {-3,16}, { 3,16},   // left of habitat
      { 6,13}, { 6,10}, { 3, 7}, { 5, 7},   // right of habitat
      { 5, 4}, { 8, 3}, { 5, 7}, { 5, 4},  // right leg
      { 8, 3}, { 8, 0}, {10, 0}, { 6, 0}   // right foot
   };

   // draw it
   glBegin(GL_LINE_STRIP);
   glColor3f(1.0, 0, 0);
   for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
        glVertex2f(point.getX() + points[i].x,
                   point.getY() + points[i].y);

   // complete drawing
  glColor3f(1, 1, 1);
  glEnd();
   
   
}


/***********************************************************************
 * DRAW Lander Flame
 * Draw the flames coming out of a moonlander for thrust
 ***********************************************************************/
void drawLanderFlames(const Point & point, 
                      bool bottom,
                      bool left,
                      bool right)
{
   // simple point
   struct PT
   {
      int x;
      int y;
   };

   int iFlame = random(0, 3);  // so the flame flickers
   
   // draw it
   glBegin(GL_LINE_LOOP);
   glColor3f(1.0 /* red % */, 0.0 /* green % */, 1.0 /* blue % */);
   
   // bottom thrust
   if (bottom)
   {
      PT points[3][3] =
      {
         { {-5,  -6}, { 0, -1}, { 3, -10} },
         { {-3,  -6}, {-1, -2}, { 0, -15} },
         { { 2, -12}, { 1,  0}, { 6,  -4} }
      };
      
      glVertex2f(point.getX() - 2, point.getY() + 2);
      for (int i = 0; i < 3; i++)
         glVertex2f(point.getX() + points[iFlame][i].x,
                   point.getY() + points[iFlame][i].y);
      glVertex2f(point.getX() + 2, point.getY() + 2);
   }

   // right thrust
   if (right)
   {
      PT points[3][3] =
      {
         { {10, 14}, { 8, 12}, {12, 12} },
         { {12, 10}, { 8, 10}, {10,  8} },
         { {14, 11}, {14, 11}, {14, 11} }
      };
      
      glVertex2f(point.getX() + 6, point.getY() + 12);
      for (int i = 0; i < 3; i++)
         glVertex2f(point.getX() + points[iFlame][i].x,
                    point.getY() + points[iFlame][i].y);
      glVertex2f(point.getX() + 6, point.getY() + 10);
   }

   // left thrust
   if (left)
   {
      PT points[3][3] =
      {
         { {-10, 14}, { -8, 12}, {-12, 12} },
         { {-12, 10}, { -8, 10}, {-10,  8} },
         { {-14, 11}, {-14, 11}, {-14, 11} }
      };
      
      glVertex2f(point.getX() - 6, point.getY() + 12);
      for (int i = 0; i < 3; i++)
         glVertex2f(point.getX() + points[iFlame][i].x,
                    point.getY() + points[iFlame][i].y);
      glVertex2f(point.getX() - 6, point.getY() + 10);
   }

   glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
   glEnd();
}


/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num < max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max)
{
   assert(min <= max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num < max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   
   assert(min <= num && num <= max);

   return num;
}


/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 *  INPUT  center    Center of the rectangle
 *         width     Horizontal size
 *         height    Vertical size
 *         rotation  Orientation
 *************************************************************************/
void drawRect(const Point & center, int width, int height, int rotation)
{
   Point tl(false /*check*/); // top left
   Point tr(false /*check*/); // top right 
   Point bl(false /*check*/); // bottom left
   Point br(false /*check*/); // bottom right

   //Top Left point
   tl.setX(center.getX() - (width  / 2));
   tl.setY(center.getY() + (height / 2));

   //Top right point
   tr.setX(center.getX() + (width  / 2));
   tr.setY(center.getY() + (height / 2));

   //Bottom left point
   bl.setX(center.getX() - (width  / 2));
   bl.setY(center.getY() - (height / 2));

   //Bottom right point
   br.setX(center.getX() + (width  / 2));
   br.setY(center.getY() - (height / 2));

   //Rotate all points the given degrees
   rotate(tl, center, rotation);
   rotate(tr, center, rotation);
   rotate(bl, center, rotation);
   rotate(br, center, rotation);

   //Finally draw the rectangle
   glBegin(GL_LINE_STRIP);
   glVertex2f(tl.getX(), tl.getY());
   glVertex2f(tr.getX(), tr.getY());
   glVertex2f(br.getX(), br.getY());
   glVertex2f(bl.getX(), bl.getY());
   glVertex2f(tl.getX(), tl.getY());
   glEnd();
}

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the circle
 *          radius   Size of the circle
 *************************************************************************/
void drawCircle(const Point & center, int radius)
{
   assert(radius > 1.0);
   const double increment = 1.0 / (double)radius;

   // begin drawing
   glBegin(GL_LINE_LOOP);

   // go around the circle
   for (double radians = 0; radians < M_PI * 2.0; radians += increment)
      glVertex2f(center.getX() + (radius * cos(radians)),
                 center.getY() + (radius * sin(radians)));
   
   // complete drawing
   glEnd();   
}

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *  INPUT point   The position of the dow
 *************************************************************************/
void drawDot(const Point & point)
{
   // Get ready, get set...
   glBegin(GL_POINTS);

   // Go...
   glVertex2f(point.getX(),     point.getY()    );
   glVertex2f(point.getX() + 1, point.getY()    );
   glVertex2f(point.getX() + 1, point.getY() + 1);
   glVertex2f(point.getX(),     point.getY() + 1);

   // Done!  OK, that was a bit too dramatic
   glEnd();
}

/************************************************************************
 * DRAW RED DOT
 * Draw a single RED point on the screen, 2 pixels by 2 pixels
 *  INPUT point   The position of the dow
 *************************************************************************/
void drawRedDot(const Point & point)
{
  // Get ready, get set...
  glColor3f(1,0,0);
  glBegin(GL_POINTS);

  // Go...
  glVertex2f(point.getX(),     point.getY()    );
  glVertex2f(point.getX() + 1, point.getY()    );
  glVertex2f(point.getX() + 1, point.getY() + 1);
  glVertex2f(point.getX(),     point.getY() + 1);
  glColor3f(1,1,1);
  // Done!  OK, that was a bit too dramatic
  glEnd();
}

/****************
* Draw Round.
****************/
void drawRound(const Point & point, int rotation)
{
  Point up(point.getX(), point.getY() + 2);
  rotate(up, point, rotation);
  Point down(point.getX(), point.getY() - 2);
  rotate(down, point, rotation);
  drawDot(up);
  drawRedDot(point);
  drawDot(down);
}

/************************************************************************
 * DRAW Tough Bird
 * Draw a tough bird on the screen
 *  INPUT point   The position of the sacred
 *        radius  The size of the bird
 *        hits    How many its remaining to kill the bird 
 *************************************************************************/
void drawToughBird(const Point & center, float radius)
{
   assert(radius >= 1.0);
   const double increment = M_PI / 6.0;
   
   // begin drawing
   glBegin(GL_TRIANGLES);   
   glColor3f(1,0,0);

   // three points: center, pt1, pt2
   Point pt1(false /*check*/);
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));   
   Point pt2(pt1);

   // go around the circle
   for (double radians = increment;
        radians <= M_PI * 2.0 + .5;
        radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f(center.getX(), center.getY());
      glVertex2f(pt1.getX(),    pt1.getY()   );
      glVertex2f(pt2.getX(),    pt2.getY()   );
      
      pt1 = pt2;
   }
      
   // complete drawing
   glColor3f(1,1,1);
   glEnd();   
}

void drawTeleport(const Point & center, float radius)
{
   assert(radius >= 1.0);
   const double increment = M_PI / 6.0;
   
   // begin drawing
   glBegin(GL_TRIANGLES);   
   glColor3f(.4,.2,1);

   // three points: center, pt1, pt2
   Point pt1(false /*check*/);
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));   
   Point pt2(pt1);

   // go around the circle
   for (double radians = increment;
        radians <= M_PI * 2.0 + .5;
        radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f(center.getX(), center.getY());
      glVertex2f(pt1.getX(),    pt1.getY()   );
      glVertex2f(pt2.getX(),    pt2.getY()   );
      
      pt1 = pt2;
   }
      
   // complete drawing
   glColor3f(1,1,1);
   glEnd();   
}

/************************************************************************
 * DRAW Sacred Bird
 * Draw a sacred bird on the screen
 *  INPUT point   The position of the sacred
 *        radius  The size of the bird
 *************************************************************************/
void drawSacredBird(const Point & center, float radius)
{
   // handle auto-rotation
   static float rotation = 0.0;   
   rotation += 5.0;

   
   // begin drawing
   glBegin(GL_LINE_LOOP);
   glColor3f(1.0 /* red % */, 0.0 /* green % */, 1.0 /* blue % */);

   
   //loop around a circle the given number of times drawing a line from
   //one point to the next
   for (int i = 0; i < 5; i++)
   {
      Point temp(false /*check*/);
      float radian = (float)i * (M_PI * 2.0) * 0.4;
      temp.setX(center.getX() + (radius * cos(radian)));
      temp.setY(center.getY() + (radius * sin(radian)));
      rotate(temp, center, rotation);
      glVertex2f(temp.getX(), temp.getY());
   }
   
   // complete drawing
   glColor3f(1.0, 1.0, 1.0); // reset to white
   glEnd();   
}

/**********************************************************************
 * DRAW SMALL ASTEROID
 **********************************************************************/
void drawSmallAsteroid( const Point & center, int rotation, int r, int g, int b)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {-5, 9},  {4, 8},   {8, 4},   
      {8, -5},  {-2, -8}, {-2, -3}, 
      {-8, -4}, {-8, 4},  {-5, 10}
   };
   
   glColor3f(r, g, b);
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1, 1, 1);
   glEnd();
}

/**********************************************************************
 * DRAW MEDIUM ASTEROID
 **********************************************************************/
void drawMediumAsteroid( const Point & center, int rotation, int r, int g, int b)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {2, 8},    {8, 15},    {12, 8}, 
      {6, 2},    {12, -6},   {2, -15},
      {-6, -15}, {-14, -10}, {-15, 0},
      {-4, 15},  {2, 8}
   };
   glColor3f(r, g, b);
   
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1, 1, 1);
   glEnd();
}

/**********************************************************************
 * DRAW LARGE ASTEROID
 **********************************************************************/
void drawLargeAsteroid( const Point & center, int rotation, int r, int g, int b)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {0, 12},    {8, 20}, {16, 14},
      {10, 12},   {20, 0}, {0, -20},
      {-18, -10}, {-20, -2}, {-20, 14},
      {-10, 20},  {0, 12}
   };
   glColor3f(r, g, b);
   
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1, 1, 1);
   glEnd();
}

/**********************************************************************
 * DRAW LARGE ASTEROID
 **********************************************************************/
void drawHugeAsteroid( const Point & center, int rotation, int r, int g, int b, int cracks)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {50, 0}, {40, 30}, {30, 40}, {20, 45}, {10, 20}, {0, 50},
      {0, 50}, {-10, 50}, {-20, 45}, {-30, 40}, {-40, 30}, {-50, 0},
      {-50, 0}, {-40, -30}, {-30, -40}, {-20, -45}, {0, -50},
      {0, -50}, {10, -50}, {20, -45}, {30, -40}, {40, -30}, {50, 0}
   };
   glColor3f(r, g, b);
   
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1, 1, 1);
   glEnd();
   if (cracks >= 2)
   {
    struct PT2
    {
      int x;
      int y;
    } points[] =
    { 
        {10, 20}, {0, 0}, {-20, 0}, {-10, 0}, {-15, 10}, {-10, 0}
    };
    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(points)/sizeof(PT2); i++)
    {
       Point pt(center.getX() + points[i].x, 
                center.getY() + points[i].y);
       rotate(pt, center, rotation);
       glVertex2f(pt.getX(), pt.getY());
    }
    glColor3f(1, 1, 1);
    glEnd();
   }
}

/**********************************************************************
 * DRAW LARGE ASTEROID
 **********************************************************************/
void drawBehemothAsteroid( const Point & center, int rotation, int r, int g, int b)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {150, 0}, {130, 70}, {100, 80}, {80, 80}, {50, 100}, {30, 100}, {0, 150},
      {-20, 140}, {-50, 130}, {-70, 120}, {-100, 70}, {-120, 50}, {-130, 30}, {-150, 0},
      {-150, -30}, {-130, -50}, {-100, -70}, {-90, -90}, {-40, -100}, {-20, -110}, {0, -120},
      {20, -120}, {30, -110}, {40, -100}, {70, -80},  {100, -60}, {130, -50}, {150, 0}
   };
   glColor3f(r, g, b);
   
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1, 1, 1);
   glEnd();
}

/************************************************************************       
 * DRAW Ship                                                                    
 * Draw a spaceship on the screen                                               
 *  INPUT point   The position of the ship                                      
 *        angle   Which direction it is ponted                                  
 *************************************************************************/
void drawShip(const Point & center, int rotation, int thrust)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   };
   
   // draw the ship                                                 
   const PT pointsShip[] = 
   { // top   r.wing   r.engine l.engine  l.wing    top
      {0, 6}, {6, -6}, {2, -3}, {-2, -3}, {-6, -6}, {0, 6}  
   };
   
   glBegin(GL_LINE_STRIP);
   glColor3f(1,0,1);
   for (int i = 0; i < sizeof(pointsShip)/sizeof(PT); i++)
   {
      Point pt(center.getX() + pointsShip[i].x, 
               center.getY() + pointsShip[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1,1,1);
   glEnd();

   // draw the flame if necessary
   if (thrust == 1)
   {
      const PT pointsFlame[3][5] =
      {
         { {-2, -5}, {-2, -20}, { 0, -6}, { 2, -13}, {2, -3} },
         { {-2, -5}, {-4, -15}, {-1, -7}, { 1, -14}, {2, -3} },
         { {-2, -5}, {-1, -22}, { 1, -7}, { 4,  -9}, {2, -3} }
      };
      
      glBegin(GL_LINE_STRIP);
      glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
      int iFlame = random(0, 3);
      for (int i = 0; i < 5; i++)
      {
         Point pt(center.getX() + pointsFlame[iFlame][i].x, 
                  center.getY() + pointsFlame[iFlame][i].y);
         rotate(pt, center, rotation);
         glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1.0, 1.0, 1.0); // reset to white                                  
      glEnd();
   }

   if (thrust == 2)
   {
      const PT pointsFlame[3][5] =
      {
         { {-3, -5}, {-3, -30}, { 0, -6}, { 3, -23}, {3, -3} },
         { {-3, -5}, {-4, -25}, {-2, -7}, { 2, -24}, {3, -3} },
         { {-3, -5}, {-2, -32}, { 2, -7}, { 4, -19}, {3, -3} }
      };
      
      glBegin(GL_LINE_STRIP);
      glColor3f(0 /* red % */, 1.0 /* green % */, 0.0 /* blue % */);
      int iFlame = random(0, 3);
      for (int i = 0; i < 5; i++)
      {
         Point pt(center.getX() + pointsFlame[iFlame][i].x, 
                  center.getY() + pointsFlame[iFlame][i].y);
         rotate(pt, center, rotation);
         glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1.0, 1.0, 1.0); // reset to white                                  
      glEnd();

      const PT pointsFlame2[3][5] =
      {
         { {-2, -5}, {-2, -20}, { 0, -6}, { 2, -13}, {2, -3} },
         { {-2, -5}, {-4, -15}, {-1, -7}, { 1, -14}, {2, -3} },
         { {-2, -5}, {-1, -22}, { 1, -7}, { 4,  -9}, {2, -3} }
      };
      
      glBegin(GL_LINE_STRIP);
      int jFlame = random(0, 3);
      for (int i = 0; i < 5; i++)
      {
         Point pt(center.getX() + pointsFlame2[jFlame][i].x, 
                  center.getY() + pointsFlame2[jFlame][i].y);
         rotate(pt, center, rotation);
         glVertex2f(pt.getX(), pt.getY());
      }
      glEnd();
   }
}

/************************************************************************       
 * DRAW Ship                                                                    
 * Draw a spaceship on the screen                                               
 *  INPUT point   The position of the ship                                      
 *        angle   Which direction it is ponted                                  
 *************************************************************************/
void drawSniper(const Point & center, int rotation, int thrust, bool scope)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   };
   
   // draw the ship                                                 
   const PT pointsShip[] = 
   { // top   r.wing   r.engine l.engine  l.wing    top
      {0, 9}, {6, -6}, {2, -3}, {-2, -3}, {-6, -6}, {0, 9}, {0, 0}, {-2, 0}, {2, 0}  
   };
   
   glBegin(GL_LINE_STRIP);
   glColor3f(.2,.5,1);
   for (int i = 0; i < sizeof(pointsShip)/sizeof(PT); i++)
   {
      Point pt(center.getX() + pointsShip[i].x, 
               center.getY() + pointsShip[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1,1,1);
   glEnd();

   // draw the flame if necessary
   if (thrust == 1)
   {
      const PT pointsFlame[3][5] =
      {
         { {-2, -5}, {-2, -20}, { 0, -6}, { 2, -13}, {2, -3} },
         { {-2, -5}, {-4, -15}, {-1, -7}, { 1, -14}, {2, -3} },
         { {-2, -5}, {-1, -22}, { 1, -7}, { 4,  -9}, {2, -3} }
      };
      
      glBegin(GL_LINE_STRIP);
      glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
      int iFlame = random(0, 3);
      for (int i = 0; i < 5; i++)
      {
         Point pt(center.getX() + pointsFlame[iFlame][i].x, 
                  center.getY() + pointsFlame[iFlame][i].y);
         rotate(pt, center, rotation);
         glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1.0, 1.0, 1.0); // reset to white                                  
      glEnd();
   }
   if (scope)
   {
      const PT aim[] = 
      {
        {0, 10}, {0, 500}
      };
      glBegin(GL_LINE_STRIP);
      glColor3f(.5, 0.0, 0.0);
      for (int i = 0; i < 2; i++)
      {
        Point pt(center.getX() + aim[i].x, center.getY() + aim[i].y);
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1, 1, 1);
      glEnd();
   }
}

void drawTank(const Point & center, int rotation, int thrust)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   };
   
   // draw the ship                                                 
   const PT pointsShip[] = 
   { // top   r.wing   r.engine l.engine  l.wing    top
      {6, 0}, {12, 0}, {6, 6}, {6, 0}, {6, 10}, {3, 15}, {3, 6}, {-3, 6}, {-3, 15}, {-6, 10}, {-6, 0}, {-6, 6}, {-12, 0}, {-6, 0}, {-2, -3}, {2, -3}, {6, 0}
   };
   
   glBegin(GL_LINE_STRIP);
   glColor3f(.7, .5, .2);
   for (int i = 0; i < sizeof(pointsShip)/sizeof(PT); i++)
   {
      Point pt(center.getX() + pointsShip[i].x, 
               center.getY() + pointsShip[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1,1,1);
   glEnd();

   // draw the flame if necessary
   if (thrust == 1)
   {
      const PT pointsFlame[3][5] =
      {
         { {-2, -5}, {-2, -20}, { 0, -6}, { 2, -13}, {2, -3} },
         { {-2, -5}, {-4, -15}, {-1, -7}, { 1, -14}, {2, -3} },
         { {-2, -5}, {-1, -22}, { 1, -7}, { 4,  -9}, {2, -3} }
      };
      
      glBegin(GL_LINE_STRIP);
      glColor3f(0.3 /* red % */, .5 /* green % */, 0.0 /* blue % */);
      int iFlame = random(0, 3);
      for (int i = 0; i < 5; i++)
      {
         Point pt(center.getX() + pointsFlame[iFlame][i].x, 
                  center.getY() + pointsFlame[iFlame][i].y);
         rotate(pt, center, rotation);
         glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1.0, 1.0, 1.0); // reset to white                                  
      glEnd();
  }
}

void drawSuper(const Point & center, int rotation, int thrust, bool scope)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   };
   
   // draw the ship                                                 
   const PT pointsShip[] = 
   { // top   r.wing   r.engine l.engine  l.wing    top
      {0, 5}, {8, -12}, {2, -3}, {-2, -3}, {-8, -12}, {0, 5} 
   };
   
   glBegin(GL_LINE_STRIP);
   glColor3f(.7, .7, .7);
   for (int i = 0; i < sizeof(pointsShip)/sizeof(PT); i++)
   {
      Point pt(center.getX() + pointsShip[i].x, 
               center.getY() + pointsShip[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1,1,1);
   glEnd();

   // draw the flame if necessary
   if (thrust == 1)
   {
      const PT pointsFlame[3][5] =
      {
         { {-3, -6}, {-3, -30}, { 0, -6}, { 3, -23}, {3, -3} },
         { {-3, -5}, {-4, -25}, {-2, -7}, { 2, -24}, {3, -3} },
         { {-3, -5}, {-2, -32}, { 2, -7}, { 4, -19}, {3, -3} }
      };
      
      glBegin(GL_LINE_STRIP);
      glColor3f(0.7 /* red % */, .2 /* green % */, .2 /* blue % */);
      int iFlame = random(0, 3);
      for (int i = 0; i < 5; i++)
      {
         Point pt(center.getX() + pointsFlame[iFlame][i].x, 
                  center.getY() + pointsFlame[iFlame][i].y);
         rotate(pt, center, rotation);
         glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1.0, 1.0, 1.0); // reset to white                                  
      glEnd();
   }
   if (scope)
   {
      const PT aim[] = 
      {
        {0, 10}, {0, 500}
      };
      glBegin(GL_LINE_STRIP);
      glColor3f(0.4, 0.1, 0.2);
      for (int i = 0; i < 2; i++)
      {
        Point pt(center.getX() + aim[i].x, center.getY() + aim[i].y);
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1, 1, 1);
      glEnd();
   }
}

void drawOldShip(const Point & center, int rotation, int thrust)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   };
   
   // draw the ship                                                 
   const PT pointsShip[] = 
   { // top   r.wing   r.engine l.engine  l.wing    top
      {-1, 3}, {-1, 6}, {1, 6}, {1, 3}, {3, 3}, {3, -5}, {2, -3}, {-2, -3}, {-3, -5}, {-3, 3}, {3, 3}
   };
   
   glBegin(GL_LINE_STRIP);
   glColor3f(1, 1, 1);
   for (int i = 0; i < sizeof(pointsShip)/sizeof(PT); i++)
   {
      Point pt(center.getX() + pointsShip[i].x, 
               center.getY() + pointsShip[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glColor3f(1,1,1);
   glEnd();

   // draw the flame if necessary
   if (thrust == 1)
   {
      const PT pointsFlame[3][5] =
      {
         { {-2, -3}, {-2, -10}, { 0, -6}, { 2, -8}, {2, -3} },
         { {-2, -3}, {-2, -6}, {-1, -10}, { 1, -5}, {2, -3} },
         { {-2, -3}, {-1, -12}, { 1, -7}, { 4,  -6}, {2, -3} }
      };
      
      glBegin(GL_LINE_STRIP);
      glColor3f(.7 /* red % */, .5 /* green % */, 0.0 /* blue % */);
      int iFlame = random(0, 3);
      for (int i = 0; i < 5; i++)
      {
         Point pt(center.getX() + pointsFlame[iFlame][i].x, 
                  center.getY() + pointsFlame[iFlame][i].y);
         rotate(pt, center, rotation);
         glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1.0, 1.0, 1.0); // reset to white                                  
      glEnd();
  }
}




