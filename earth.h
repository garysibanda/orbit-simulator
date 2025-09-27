/******************************
 * Header File:
 *   Earth : Constants and functions related to the earth
 *  Author:
 *  Br. Helfrich
 *  Summary:
 *  Everything we need to know about the earth
 *  **********************************/

#pragma once

#include <cassert>
#include "satellite.h"     // for the Satellite base class

/******************************
   * EARTH
   * The earth itself
   **********************************/
void drawEarth(const Position& pos, double radians);

class Earth : public Satellite
{
public:
   // Creation of the earth needs to know time dilation to get speed of rotation right
   Earth(double radiansPerFrame) : Satellite()
   {
      assert(pos.getMetersX() == 0.0);
      assert(pos.getMetersY() == 0.0);
      
      age = 100;
      
      radius = 6378000.0; // in meters
      
      angularVelocity = radiansPerFrame;
   }
   
   // just draw the earth
   virtual void draw()
   {
      drawEarth(Position(), direction.getRadians());
   }
   
   // the earth is not defucnt!
   bool getDefunct() const { return false; }
   
   // Earth does not move.
   virtual void move(double timeDilation)
   {
      direction.rotate(angularVelocity);
   }
   
   // do nothing because the earth does not explode
   virtual void kill() {  }
private:
};

