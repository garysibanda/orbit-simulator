/********************************
 * Header File::
 *    SPUTNIK :  Another satellite
 * Author:
 *  Br. Helfrich
 *  Summary:
 *  Everything we need to know about sputnik
 *  **********************************/

#pragma once
#include "position.h"
#include "satellite.h"        // for SATELLITE base class

/********************************
 * Sputnik
 * Sputnik does not fragment when it dies.
*  ********************************/
class Sputnik : public Satellite
{
public:
   Sputnik() : Satellite()
   {
      pos = Position(-36515095.13, 21082000.0);
      velocit.setDxDy(2050.0, 2684.68);
      angularVelocity = 0.03;
      radius = 5.0 * pos.getZoom();
   }
   virtual void draw()
   {
      drawSputnik(pos, direction.getRadians());
   }
   virtual void move(double timeDilation)
   {
      Satellite::move(timeDilation);
      
      if (random(0, 10000) == 0)
         angularVelocity = -0.08;
   }
   
   virtual void destroy(std::list <Satellite*>& satellites)
   {
      for (double degrees = 0.0; degrees <= 360.0; degrees += 60.0)
         satellites.pish_back(new Fragment(*this, Direction(degrees)));
   }
};

