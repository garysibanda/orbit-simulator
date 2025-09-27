/**********************************
 * Header File:
 *    STARLINK
 * Author:
 *   Br. Helfrich
 * Summary:
 *  Everything we need to know about connecting to the Starlink API
 *  **********************************/

#pragma once

#include "satellite.h"     // for SATELLITE base class

/***************************
 * Starlink Body
 * A part of a starlink
   ***************************/
class StarlinkBody : public Part
{
public:
   StarlinkBody(const Satellite& parent, const Direction& dirKick) : Part(parent + dirKick)
   {
      radius = 2.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawStarlinkBody(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      for (double degrees = 0.0; degrees <= 360.0; degrees += 120.0)
         satellites.push_back(new Fragment(*this, Direction(degrees)));
   }
};

/***************************
 * Starlink Array
 * A part of a starlink
 *  ***************************/
class StarlinkArray : public Part
{
public:
   StarlinkArray(const Satellite& parent, const Direction& dirKick) : Part(parent + dirKick)
   {
      radius = 4.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawStarlinkArray(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      for (double degrees = 0.0; degrees <= 360.0; degrees += 120.0)
         satellites.push_back(new Fragment(*this, Direction(degrees)));
   }
};

using namespace std;

/***************************
 * Starlink
   * A satellite in low earth orbit
 *   ***************************/
class Starlink : public Whole
{
public:
   Starlink() : Whole(4000)
   {
      pos = Position(0.0, -13020000.0); // 13,020 km from center of earth
      velocity = Velocity(5800.0, 0.0);
      angularVelocity = -0.008;
      direction.setDegrees(0.0);
      radius = 6.0 * pos.getZoom();
   }
   
   // draw a starlink
   virtual void draw()
   {
      drawStarlink(pos, Position(), direction.getRadians());
   }
   
   // destroy a starlink
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      satellites.push_back(new StarlinkArray(*this, Direction(90.0)));
      satellites.push_back(new StarlinkBody(*this, Direction(270.0)));
      satellites.push_back(new Fragment(*this, Direction(0.0)));
      satellites.push_back(new Fragment(*this, Direction(180.0)));
   }
};
