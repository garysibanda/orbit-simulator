/****************************
 * Header file:
 *   CREW DREAGON
 * Author:
 *  Br. Helfrich
 * Summary:
 *     Everything we need to know about the Crew Dragon ship
   *****************************/

#pragma once

#include "satellite.h"     // for SATELLITE base class

/****************************
 * DRAGON Left
 * A part of the crew DRAGON satellite
   *****************************/
class DragonLeft : public Part
{
public:
   DragonLeft(const Satellite& parent, const Direction& dirKick) : Part(parent, direction + dirKick)
   {
      radius = 6. 0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawCrewDragonLeft(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      satellites.push_back(new Fragment(*this, Direction(0.0)));
      satellites.push_back(new Fragment(*this, Direction(180.0)));
   }
};

/****************************
   * DRAGON Right
   * A part of the crew DRAGON satellite
   *****************************/
class DragonRight : public Part
{
public:
   DragonRight(const Satellite& parent, const Direction& dirKick) : Part(parent, direction + dirKick)
   {
      radius = 6.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawCrewDragonRight(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      satellites.push_back(new Fragment(*this, Direction(90.0)));
      satellites.push_back(new Fragment(*this, Direction(270.0)));
   }
};


/****************************
* DRAGON CENTER
* A part of the crew DRAGON satellite
   *****************************/
class DragonCenter : public Part
{
public:
   DragonCenter(const Satellite& parent, const Direction& dirKick) : Part(parent, direction + dirKick)
   {
      radius = 6.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawCrewDragonCenter(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      for (double degrees = 0.0; degrees < 360.0; degrees += 90.0)
         satellites.push_back(new Fragment(*this, Direction(degrees)));
   }
};

/****************************
* DRAGON
* The Space-X crew dragon
   *****************************/
class Dragon : public Whole
{
public:
   Dragon() : Whole(4000)
   {
      pos = Position(0.0, 8000000.0);
      velocity.setDxDy(-7900.0, 0.0); // 7.9 km/s
      angularVelocity = -0.01;
      radius = 7.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawCrewDragon(pos, direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      satellites.push_back(new DragonCenter( *this, Direction( 90.0)));
      satellites.push_back(new DragonLeft(   *this, Direction(  0.0)));
      satellites.push_back(new DragonRight(  *this, Direction(180.0)));
      satellites.push_back(new Fragment(     *this, Direction(330.0)));
      satellites.push_back(new Fragment(     *this, Direction(250.0)));
   }
};
 
   

