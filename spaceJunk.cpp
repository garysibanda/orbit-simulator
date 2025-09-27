/**************************************
 * 1. Name:
   *      The Key
 * 2. Assignment Name:
 *     Lab 12: Orbit Simulator
 * 3. Assignment Description:
 *     Simulate stuff orbiting the earth
 *************************************/

#include <cassert>         // for ASSERT
#include "uiInteract.h"    // for INTERFACE
#include "uiDraw.h"        // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "velocity.h"      // for VELOCITY
#include "physics.h"       // for all the physics stuff
#include "satellite.h"     // for SATELLITE
#include "earth.h"         // for EARTH
#include "gps.h"           // for GPS
#include "crewDragon.h"    // for CREWDRAGON
#include "hubble.h"        // for HUBBLE
#include "sputnik.h"       // for SPUTNIK
#include "starlink.h"      // for STARLINK
#include "ship.h"          // for SHIP
#include "fragment.h"      // for FRAGMENT
#inlude "star.h"           // for STAR
#include <list>            // for LIST
using namespace std;

#define NUM_STARS 200

/********************************************
* SIMULATOR
* The main simulation class that holds the entire world
*********************************************/
class Sim
{
public:
   // create and destroy the simulation
   Sim(const Position& ptUpperRight);
   ~Sim();
   
   // draw everything
   void draw();
   
   // update everything
   void move();
   
   // send input to everything
   void input(const Interface & ui);
   
private:
   list<Satellite *> satellites;
   Star stars[NUM_STARS];
   double timeDilation;                // how many seconds per frame
};

/********************************************
 * CONSTRUCTOR
 * Draw everything on the screen
 * *******************************************/
Sim::Sim(const Position & ptUpperRight)
{
   // every frame consume this many seconds
   double frameRate = 30.0;                                               // OpenGL draws 30 frames/second
   double hoursPerDay = 24.0;                                               // how many hours in a day
   double minutesPerHour = 60.0;                                            // how many minutes in an hour
   double secondsPerMinute = 60.0;                                          // how many seconds in a minute
   double secondsPerDay = hoursPerDay * minutesPerHour * secondsPerMinute; // how many seconds in a day
   
   timeDilation = hoursPerDay * minutesPerHour;             // 1440 minutes per day
   
   // create the stars
   for (int i = 0; i < NUM_STARS; i++)
      stars[i].reset(ptUpperRight.getPixelsX(), ptUpperRight.getPixelsY());
   
   // ship is in the corner
   satellites.push_back(new Ship);
   
   // next comes the earth. I hope it never dies!
   double radiansInADay = -3.14159 * 2.0;
   double radiansPerFrame = (radiansInADay / frameRate) * (timeDilation / secondsPerDay);
   satellites.push_back(new Earth(radiansPerFrame));
   
   // a bunch satellites
   for (int i = 0; i < 6; i++)
      satellites.push_back(new GPS(i));
   satellites.push_back(new Starlink());
   satellites.push_back(new Hubble());
   satellites.push_back(new Dragon());
   satellites.push_back(new Sputnik());
   return;
}

/********************************************
   * DESTRUCTOR
   * Roll it up like a great scroll
   * *******************************************/
Sim::~Sim()
{
   // destroy everything that was allocated.
   for (list<Satellite *>::iterator it = satellites.begin();
      it != satellites.end();
      it++)
      delete[] * it;
}

/********************************************
 * INPUT
 * Accept input from the user
 * *******************************************/
void Sim::input(const Interface & ui)
{
   for (list<Satellite *>::iterator it = satellites.begin();
      it != satellites.end();
      it++)
      (*it)->input(ui, satellites);
}

/********************************************
 * DRAW
 * Draw everything on the screen
 * *******************************************/
void Sim::draw(){
   // draw the stars
   for (int i = 0; i < NUM_STARS; i++)
      stars[i].draw();
   
   // draw the satellites
   list <Satellite*> ::iterator it;
   for (it = satellites.begin(); it != satellites.end(); it++)
      (*it)->draw();
}

/********************************************
 * MOVE
 * Advance everything on the sceen by a unit of time
 * *******************************************/
void Sim::move()
{
   list <Satellite*> ::iterator it1;
   list <Satellite*> ::iterator it2;
   double time = timeDilation / 30.0;                            // frame rate
   
   // first, advance everything according to inertia and gravity
   for (auto satellite : satellites)
      satellite->move(time);
   
   // next, check for collisions
   for (it1 = satellites.begin(); it1 != satellites.end(); it1++)
      for (it2 = satellites.begin(); it2 != satellites.end(); it2++)
         if (!(*it1)->isDead() && !(*it2)->isDead() &&
            !(*it1)->isInvisible() && !(*it2)->isInvisible())
         {
            assert(*it1 != *it2); // you can't collide with yourself
            double distance = computeDistance((*it1)->getPosition(),
                                              (*it2)->getPosition());
            if (distance < ((*it1)->getRadius() + (*it2)->getRadius()))
            {
               (*it1)->kill();
               (*it2)->kill();
            }
         }
            
   // finally, deal with collisions and any other space junk
   for (it1 = satellites.begin(); it1 != satellites.end(); )
      if ((*it1)->isDead())
      {
         (*it1)->destroy(satellites);
         it1 = satellites.erase(it1);
      }
      else
         ++it1;
}

/********************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 * *******************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Sim* pSim = (Sim*)p;
   
   // move everything in the game
   pSim->move();
   
   // draw everything
   pSim->draw();
   
   // accept input
   pSim->input(*pUI);
}

// this is reset in main()
double Position::metersFromPixels = 50.0;


/*********************************
   * Initialize the simulation and set it in motion
   *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   
   // unit tests
   testRunner();
   
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Space Junk",    /* name on the window */
      ptUpperRight);
   
   // Initialize the simulation
   Sim sim(ptUpperRight);
   
   // set everything into action
   ui.run(callBack, &sim);
   
   return 0;
}
