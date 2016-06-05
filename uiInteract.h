/*********************************************
 * Header file:
 *    UI INTERFACE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This module will create an OpenGL window,
 *    enter the OpenGL main loop, and accept events.
 *    The main methods are:
 *    1. Constructors - Create the window
 *    2. run()        - Run the main loop
 *    3. callback     - Specified in Run, this user-provided
 *                      function will get called with every frame
 *    4. isDown()     - Is a given key pressed on this loop?
 **********************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

 #include "point.h"

/********************************************
 * INTERFACE
 * All the data necessary to keep our graphics
 * state in memory
 ********************************************/
class Interface
{
public:
   // Default constructor useful for setting up the random variables
   // or for opening the file for output
   Interface() { initialize(0, 0x0000, "Window", Point(-50, 50), Point(50, -50)); };

   // Constructor if you want to set up the window with anything but
   // the default parameters
   Interface(int argc, char ** argv, const char * title, Point topLeft, Point bottomRight)
   {
      initialize(argc, argv, title, topLeft, bottomRight);
   }
   
   // Destructor, incase any housecleaning needs to occr
   ~Interface();

   // This will set the game in motion
   void run(void (*callBack)(const Interface *, void *), void *p);

   // Is it time to redraw the screen
   bool isTimeToDraw();

   // Set the next draw time based on current time and time period
   void setNextDrawTime();

   // Retrieve the next tick time... the time of the next draw.
   unsigned int getNextTick() { return nextTick; };

   // How many frames per second are we configured for?
   void setFramesPerSecond(double value);
   
   // Key event indicating a key has been pressed or not.  The callbacks
   // should be the only onces to call this
   void keyEvent(int key, bool fDown);
   void keyEvent();

   // Current frame rate
   double frameRate() const { return timePeriod;    };
   
   // Get various key events
   int  isDown()      const { return isDownPress;   };
   int  isUp()        const { return isUpPress;     };
   int  isLeft()      const { return isLeftPress;   };
   int  isRight()     const { return isRightPress;  };
   int  isRapid()     const { return isRapidPress;  };
   bool isSpace()     const { return isSpacePress;  };
   bool isZ()         const { return isZPress;      };
   bool isX()         const { return isXPress;      };
   bool isC()         const { return isCPress;      };
   bool isV()         const { return isVPress;      };
   bool isB()         const { return isBPress;      };
   bool isN()         const { return isNPress;      };
   bool isM()         const { return isMPress;      };
   bool isI()         const { return isIPress;      };
   bool isT()         const { return isTPress;      };
   bool isA()         const { return isAPress;      };
   bool isS()         const { return isSPress;      };
//   bool isD()         const { return isDPress;      };
//   bool isF()         const { return isFPress;      };
   
   static void *p;                   // for client
   static void (*callBack)(const Interface *, void *);

private:
   void initialize(int argc, char ** argv, const char * title, Point topLeft, Point bottomRight);

   static bool         initialized;  // only run the constructor once!
   static double       timePeriod;   // interval between frame draws
   static unsigned int nextTick;     // time (from clock()) of our next draw

   static int  isDownPress;          // is the down arrow currently pressed?
   static int  isUpPress;            //    "   up         "
   static int  isLeftPress;          //    "   left       "
   static int  isRightPress;         //    "   right      "
   static int  isRapidPress;
   static bool isSpacePress;         //    "   space      "
   static bool isZPress;
   static bool isXPress;
   static bool isCPress;             //    "   c          "
   static bool isVPress;
   static bool isBPress;
   static bool isNPress;
   static bool isMPress;
   static bool isIPress;
   static bool isTPress;
   static bool isAPress;
   static bool isSPress;
//   static bool isDPress;
//   static bool isFPress;

};



/************************************************************************
 * DRAW CALLBACK
 * This is the main callback from OpenGL. It gets called constantly by
 * the graphics engine to refresh and draw the window.  Here we will
 * clear the background buffer, draw on it, and send it to the forefront
 * when the appropriate time period has passsed.
 *
 * Note: This and all other callbacks can't be member functions, they must
 * have global scope for OpenGL to see them.
 *************************************************************************/
void drawCallback();

/************************************************************************
 * KEY DOWN CALLBACK
 * When a key on the keyboard has been pressed, we need to pass that
 * on to the client.  Currnetly, we are only registering the arrow keys
 *************************************************************************/
void keyDownCallback(int key, int x, int y);

/************************************************************************
 * KEY UP CALLBACK
 * When the user has released the key, we need to reset the pressed flag
 *************************************************************************/
void keyUpCallback(int key, int x, int y);

/***************************************************************
 * KEYBOARD CALLBACK
 * Generic callback to a regular ascii keyboard event, such as
 * the space bar or the letter 'q'
 ***************************************************************/
void keyboardCallback(unsigned char key, int x, int y);

/************************************************************************
 * RUN
 * Set the game in action.  We will get control back in our drawCallback
 *************************************************************************/
void run();

#endif // UI_INTERFACE_H
