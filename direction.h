/********************************
 * Header File:
 *    Direction : The direction/angle of travel
 * Author:
 *   Br. Helfrich, Gary Sibanda
 * Summary:
 *   Everything we need to know about direction. 0 degerees is straight up
 **************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>           // for M_PI, COS, SIN, ATAN2
#include <iostream>        // for OSTREAM and ISTREAM

#ifdef M_PI
#define M_PI         3.14159265358979323846
#define M_PI_2       1.57079632679489661923
#endif                     // M_PI

/********************************
 * DEGREES FROM RADIANS
 * radians / 2 pi = degrees / 360
 * ********************************/
inline double degreesFromRadians(double radians)
{
   return 360.0 * (radians / (2.0 * M_PI));
}

/********************************
   * RADIANS FROM DEGREES
   * degrees / 360 = radians / 2 pi
   * ********************************/
inline double radiansFromDegrees(double degrees)
{
   return (degrees / 360.0) * (2.0 * M_PI);
}

/*********************************
 * Direction
 * Which way did he go? Which way did he go?
   **********************************/
class Direction
{
public:
   // constructors and assignment operator
   Direction() : radians(0.0) {}
   Direction(double degrees) : radians(0.0)
   {
      radians = radiansFromDegrees(degrees);
   }
   Direction(const Direction & rhs) : radians(rhs.radians) {}
   Direction& operator = (const Direction& rhs)
   {
      radians = rhs.radians;
      return *this;
   }
   
   // setters. Keep radians between -PI to PI
   void setRadians(double rhs)
   {
      if (rhs >= 0.0)
      {
         double rotations = (double)(int)(rhs / (2.0 * M_PI));
         rhs -= rotations * (2.0 * M_PI);
      }
      else
      {
         double rotations = -(double)(int)((rhs - M_PI) / (2.0 * M_PI));
         rhs += rotations * (2.0 * M_PI);
      }
      radians = rhs;
   }
   void setDegrees(double rhs) { radians = radiansFromDegrees(rhs);  }
   // set based on the components
   void setDxDy(double dx, double dy)
   {
      radians = atan2(dx, dy);
   }
   
   void setDown()       { radians = M_PI;    }
   void setUp()         { radians = 0.0;     }
   void setRight()      { radians = M_PI_2;  }
   void setLeft()       { radians = -M_PI_2; }
   void reverse()
   {
      setRadians(radians + M_PI);
   }
   
   // rotate by an amount in radians
   void rotate(double amount)
   {
      radians += amount;
      if (radians > M_PI)
         radians -= 2.0 * M_PI;
      if (radians < -M_PI)
         radians += 2.0 * M_PI;
   }
   
   // getters
   double getRadians() const { return radians;                     }
   double getDegrees() const { return degreesFromRadians(radians);  }
   
   // retrueve the components
   // dy = cos a
   // dx = sin a
   double getDx() const { return sin(radians); }
   double getDy() const { return cos(radians); }
   
   bool isRight() const { return radians > 0.0 && radians <  M_PI;   }
   bool isLeft()  const { return radians < 0.0 && radians > -M_PI;   }
   
   Direction operator+(double degrees) const
   {
      return Direction(getDegrees() + degrees);
   }
   
   Direction operator+(Direction rhs) const
   {
      rhs.rotate(radians);
      return rhs;
   }
   
   
private:
   double radians;  // angle in radians where 0 is up, + is right, - is left
};

/*********************************************
 * INPUT DEGREES
 * Accept input in degrees
 * *********************************************/
inline std::istream& operator >> (std::istream& in, Direction& rhs)
{
   double degrees;
   in >> degrees;
   rhs.setRadians(radiansFromDegrees(degrees));
   return in;
}

/*********************************************
   * OUTPUT DEGREES
   * Display output in degrees
   * *********************************************/
inline std::ostream& operator << (std::ostream& out, const Direction& rhs)
{
   out << rhs.getDegrees() << " degrees";
   return out;
}
