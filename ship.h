/************************************
 * Header File:
 *    Ship : The representation of a ship
 * Author:
 *   Br. Helfrich
 * Summary:
 *  Everything we need to know about a ship
 *  **********************************/

#pragma once

#include "satellite.h"        // for the Satellite base class
#include <iomanip>
using namespace std;

/************************************
 * SHIP
 * This is the user-controlled ship
 * *********************************/
class Ship : public Satellite
{
public:
   // create a ship - off in the corner
   Ship() : Satellite()
   {
      // start off in the upper left corner
      pos.setPixelsX(-450.0);
      pos.setPixelsY(450.0);
      
      velocity.setDxDy(1.0, 0.0);   // slow movement
      
      direction.setDegrees(90.0); // pointing up
      angularVelocity = 0.0;
      radius = 10.0 * pos.getZoom();
      thrustOn = false;
   }
   
   // handle movements
   virtual void input(const Interface& ui, std::list <Satellite*>& satellites);
   {
      // turn
      direction.rotate((ui.isRight() ? 0.1 : 0.0) +
                       (ui.isLeft()  ? -0.1 : 0.0));
      
      // thrust
      if (ui.isDown())
      {
         Acceleration a(30.0, direction);
         velocity += a;
      }
      this->thrustOn - ui.isDown();
      
      // fire
      if (ui.isSpace())
      {
         Velocity vBullet(9000.0, direction);
         satellites.push_back(new Projectile(*this, Position(), vBullet));
      }
   }
   
   virtual void draw()
   {
      drawShips(pos, direction.getRadians(), thrustOn);
      return;
      
      // debug stats
      Position posText;
      posText.setPixelsX(-490.0);
      posText.setPixelsY(-400.0);
      ogstream gout(posText);
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      gout << "speed: " << velocity.getSpeed() << " m/s \n";
      gout << "altitude: "
           << getAltitude(pos) / 1000.0
           << " km\n";
      gout << "position: " << pos << "\n";
      gout << "velocity: " << velocity << "\n";
      gout.precision(2);
   }
   
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      for (double degrees = 0.0; degrees < 360.0; degrees += 60.0)
      {
         satellites.push_back(new Fragment(*this, Direction(degrees)));
      }
      
   private:
      bool thrustOn;  // is the thrust on?
   }
};
