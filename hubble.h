/**************************
 * Header File:
 *    HUBBLE
 * Author:
 *   Br. Helfrich
 *   Summary:
 *   Everything we need to know about the Hubble Space Telescope
 *  **************************************************/

#pragma once

#include "satellite.h"     // for SATELLITE base class

/*****************************
* HUBBLE Telescope
* A part of the Hubble space telescope
******************************/
class HubbleTelescope : public Part
{
public:
   HubbleTelescope(const Satellite& parent, const Direction& dirKick) : Part(parent, direction + dirKick)
   {
      radius = 10.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawHubbleTelescope(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      for (double degrees = 0.0; degrees < 360.0; degrees += 90.0)
         satellites.push_back(new Fragment(*this, Direction(degrees)));
   }
};

/*****************************
* HUBBLE Computer
* A part of the Hubble space telescope
******************************/
class HubbleComputer : public Part
{
public:
   HubbleComputer(const Satellite& parent, const Direction& dirKick) : Part(parent, direction + dirKick)
   {
      radius = 7.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawHubbleComputer(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      satellites.push_back(new Fragment(*this, Direction(45.0)));
      satellites.push_back(new Fragment(*this, Direction(225.0)));
   }
};

/*****************************
* HUBBLE Left
* A part of the Hubble space telescope
******************************/
class HubbleLeft : public Part
{
public:
   HubbleLeft(const Satellite& parent, const Direction& dirKick) : Part(parent, direction + dirKick)
   {
      radius = 8.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawHubbleLeft(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      satellites.push_back(new Fragment(*this, Direction(0.0)));
      satellites.push_back(new Fragment(*this, Direction(180.0)));
   }
};

/*****************************
* HUBBLE Right
* A part of the Hubble space telescope
******************************/
class HubbleRight : public Part
{
public:
   HubbleRight(const Satellite& parent, const Direction& dirKick) : Part(parent, direction + dirKick)
   {
      radius = 8.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawHubbleRight(pos, Position(), direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      satellites.push_back(new Fragment(*this, Direction(90.0)));
      satellites.push_back(new Fragment(*this, Direction(270.0)));
   }
};
   
/*****************************
 * HUBBLE
   * The Hubble Space Telescope
 *   ******************************/
class Hubble : public Whole
{
public:
   Hubble() : Whole(4000)
   {
      angularVelocity = 0.0;
      pos = Position(0.0, -4216000.0);
      velocity.setDxDy( 3100.0, 0.0):
      direction.setDegrees(10.0);
   }
   virtual void draw()
   {
      drawHubble(pos, direction.getRadians());
   }
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      satellites.push_back(new HubbleTelescope(*this, Direction(0.0)));
      satellites.push_back(new HubbleComputer (*this, Direction(270.0)));
      satellites.push_back(new HubbleLeft     (*this, Direction(0.0)));
      satellites.push_back(new HubbleRight    (*this, Direction(180.0)));
   }
};
