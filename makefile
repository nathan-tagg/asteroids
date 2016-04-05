###############################################################
# Program:
#     Prove 13, Project - Asteroids
#     Brother Comeau, CS165
# Author:
#     Nathan Tagg
# Above and beyond:
#
#	- I truly went above and beyond on this assignment, and I beleive I deserve extra credit.
#
#	- I made the game widow be 1200 X 900 pixels wide. It's just better that way.
#
#	- Pressing 'x' inverts or reverts the controls.
#
#	- I changed the draw function for bullets to be pill - shaped rounds that spin around the center point.
#
#	- I created 6 total different ships. each with individual advantages / disadvantages and perks.
#	- the ships can be accesed by pressing the keys 'c', 'v', 'b', 'n', and 'm'.
#	
#	- Pressing 'c' turns your ship into a moon lander, witch is more effective at evading asteroids. 
#	Pressing 'c' again as a moon lander makes the lander flash red, and then lay a mine witch lasts 1000 frames.
#	The moon lander drops rounds straight down as apposed to directionaly.
#	
#	- Pressing 'v' turns your ship into a spacer, witch is faster than the moon lander. 
#	Pressing 'v' again as a spacer allows the user to teleport to a safe location. 
#	If teleportation fails, the spacer will flash red. Teleportation is sucessful, the spacer flashes blue.
# 	Holding the down arrow key as a spacer activates the turbo booster, witch accelerates the spacer 3X normal speed.
#	The spacer shoots normal rounds directionaly.
#	
#	- Pressing 'b' turns your ship into a sniper, witch moves and handles more sluggishly than the normal spacer.
#	Pressing 'b' again as a sniper activates the scope, witch makes it easier to target distant asteroids.
#	Holding the down arrow key as a sniper auto targets the closest asteroid withing a 300 pixel radius,
#	making it easier to destroy. As an important side note, the auto target also takes into account the trajectory 
# 	and distance of the asteroid it is targeting, and targets accordingly.
#	The sniper fires more powerful lasers witch cut through asteroids without dying and travel much faster and further than normal rounds.
#
#	- Pressing 'n' turns your ship into a gunner, witch has a quicker rotation speed than the normal spacer.
#	Holding the down arrow key as a gunner activates the airbreaks, witch bring the craft to a halt, witch can be very usefull.
#	Holding down the space bar as a gunner fires a continuous stream of regular bullets, witch travel shorter distances.
# 	(Hint - float towards a group of asteroids holding down one of the side arrow keys and the space bar for hours of fun)
#	
#	- Pressing 'm' turns your ship into the feeble ship.
#	The feeble ship is smaller, slower and less agile than other ships.
#	The feeble ship fires weak bullets that travel short distances.
#	Holding the down arrow key and pressing 't' (this is supossed to be the SECRET COMBO) 
#	as the feeble ship transforns your feeble ship into the all - powerfull SUPER SPACER.
#	
#	- The SECRET COMBO (as seen above) transforms your ship into the all - powerfull SUPER SPACER.
#	The super spacer travels faster than any other ship (1.3 times faster than the spacers' turbo).
#	Pressing 't' as the spacer teleports it to safety, and leaves a mine in its' place to destroy oncomming asteroids.
#	Holding down the space bar as a super spacer activates a scope and clocks down rotation to boost accuracy.
#	Holding down the space bar as a super spacer also fires a continuous stream of 'bolts' - witch travel fast and far, and don't die on collision, but rather cut through asteroids.
#	holding down the down arrow key as a super spacer activates the auto target feature. This - combined with the continuous stream of bullets makes for an insanely OP combo.
#	Holding down the down arrow key as a super spacer also activates the air lock, witch brings the super spacer to a halt.
#
#	-I made it so that asteroids are immortal for a few frames after they spawn. 
#	(either at the beginning of the game or when larger asteroirds break into smaller ones)
#	immortal asteroids glow red hot.
#
#	-I changed all vecors and lists to lists of pointers, and took other steps to optimize my code. 
#	The whole program runs useing about 1.2% of the CPU (recorded using the WATCH command on my MAC).
#
#	-I altered the makefile to be able to detect what kind of OS it is running on and compile accordinly.
#	It is capable of detecting the difference between MAC OSX and Linux, and will make the program differently for each.
#	(This took a good deal of research).
#
#	-I made the game endless - it will continually delete unused memory and create new memory for new rocks as the user's score goes up.
#
#	-I hope you have as much fun playing this game as I did making it! and whatever you do... Do NOT press 'i'.	
#
###############################################################

OS := $(shell uname)
ifeq ($(OS),Darwin)
	LFLAGS = -framework GLUT -framework OpenGL
else
	LFLAGS = -lglut -lGLU -lGL
endif


###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o bullet.o ship.o rock.o spacer.o sniper.o lander.o tank.o oldy.o superSpacer.o hugeRock.o largeRock.o mediumRock.o smallRock.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o bullet.o ship.o rock.o spacer.o sniper.o lander.o tank.o oldy.o superSpacer.o hugeRock.o largeRock.o mediumRock.o smallRock.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
#    ground.o      Handles the ground / world
#    game.o        Handles the game interaction
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

velocity.o: velocity.cpp velocity.h
	g++ -c velocity.cpp

game.o: game.cpp game.h 
	g++ -c game.cpp

driver.o: game.h uiInteract.h driver.cpp
	g++ -c driver.cpp

flyingObject.o: flyingObject.cpp flyingObject.h
	g++ -c flyingObject.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h 
	g++ -c bullet.cpp

ship.o: ship.cpp ship.h flyingObject.h
	g++ -c ship.cpp

rock.o: rock.cpp rock.h flyingObject.h
	g++ -c rock.cpp

spacer.o: spacer.cpp spacer.h ship.h flyingObject.h
	g++ -c spacer.cpp

sniper.o: sniper.cpp sniper.h ship.h flyingObject.h
	g++ -c sniper.cpp

lander.o: lander.cpp lander.h ship.h flyingObject.h
	g++ -c lander.cpp

tank.o: tank.cpp tank.h ship.h flyingObject.h
	g++ -c tank.cpp

oldy.o: oldy.cpp oldy.h ship.h flyingObject.h
	g++ -c oldy.cpp

superSpacer.o: superSpacer.cpp superSpacer.h ship.h flyingObject.h
	g++ -c superSpacer.cpp

hugeRock.o: hugeRock.cpp hugeRock.h rock.h flyingObject.h
	g++ -c hugeRock.cpp

largeRock.o: largeRock.cpp largeRock.h rock.h flyingObject.h
	g++ -c largeRock.cpp

mediumRock.o: mediumRock.cpp mediumRock.h rock.h flyingObject.h
	g++ -c mediumRock.cpp

smallRock.o: smallRock.cpp smallRock.h rock.h flyingObject.h
	g++ -c smallRock.cpp

#######################################################################
# ADD YOUR ADDITIONAL RULES HERE!
#
# Then, don't forget to add them to the dependecy list for a.out above.
#######################################################################


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
