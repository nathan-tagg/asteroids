/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/


#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Point
{
public:
   // constructors
   Point()            : x(0.0), y(0.0)  {}
   Point(bool check)  : x(0.0), y(0.0)  {}
   Point(float x, float y);

   // getters
   float getX()       const { return x;              }
   float getY()       const { return y;              }

   // setters
   void setX(float x);
   void setY(float y);
   void addX(float dx)      { setX(getX() + dx);     }
   void addY(float dy)      { setY(getY() + dy);     }

   friend int operator - (const Point & lhs, const Point & rhs)    // non - member friend
   {
      int distance = (sqrtf((lhs.getX() - rhs.getX()) * (lhs.getX() - rhs.getX()) + (lhs.getY() - rhs.getY()) * (lhs.getY() - rhs.getY())));
      return distance;  // returns non default constructor
   }

private:
   float x;           // horizontal position
   float y;           // vertical position
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

#endif // POINT_H
