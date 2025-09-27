/***************************
 * SOURCE File:
 *   Velocity : The velocity of an object
 * Author:
 *    Br. Helfrich, Gary Sibanda
 * Summary:
 *       Everything we need to know about speed
 *
 ****************************************/

#include "velocity.h"

#define _USE_MATH_DEFINES
#include <cmath>           // for SQRT

/*********************************************
 * Velocity : GET SPEED
 *  Compute the speed from the DX and DY
 *  a^2 + b^2 = c^2
 *  where: a = dx, b = dy, c = speed
 *
 * c = sqrt(a^2 + b^2)
 * ********************************************/

double Velocity::getSpeed() const
{
   return sqrt((dx * dx) + (dy * dy));
}


/*********************************************
   * Velocity : GET DIRECTION
   * Determine the direction things are going from the DX and DY
   * where 0 is up. This returns angle (clockwise) in radians
   ********************************************/

Direction Velocity :: getDirection() const
{
   Direction d;
   d.setDxDy(dx, dy);
   return d;
}

/*********************************************
   * Velocity : : Set SpeedDirection
   * Set both the speed and the direction
   * dy = speed cos a
   * dx = speed sin a
   ********************************************/
void Velocity :: setSpeedDirection(double speed, const Direction & direction)
{
   dy = speed * direction.getDy();
   dx = speed * direction.getDx();
}

/*********************************************
 * ACCELERATION : : Set Acceleration Direction
 * Set both the speed and the direction
 *
 * dy = speed cos a
 * dx = speed sin a
 * ********************************************/
void Acceleration :: setAccelerationDirection(double accel, const Direction& direction)
{
   ddy = accel * direction.getDy();
   ddx = accel * direction.getDx();
}

/*********************************************
 * Velocity : : DISPLAY
 **********************************************/
std::ostream& operator << (std::ostream& out, const Velocity& v)
{
   out << "[" << v.getDX() << "m/s, " << v.getDY() << "m/s]";
   return out;
}
