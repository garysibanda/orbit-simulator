/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Gary Sibanda
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/ 

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()
#include <cassert>

/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   dx += acceleration.getDDX() * time;
   dy += acceleration.getDDY() * time;
}


/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    /speed or magnitude
 *     | a /
 *     |  /
 *     | /
 *            _____________
 *  speed = \/ dx^2 + dy^2
 *********************************************/
double Velocity::getSpeed() const
{
   return sqrt((dx * dx) + (dy * dy));
}

/*********************************************
 * VELOCITY : SET
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    /speed or magnitude
 *     | a /
 *     |  /
 *     | /
 * dy = speed cos(a)
 * dx = speed sin(a)
 *********************************************/
void Velocity::set(const Angle & angle, double magnitude)
{
   dx = magnitude * sin(angle.getRadians());
   dy = magnitude * cos(angle.getRadians());
}


/************************************************
 * Velocity :: GET ANGLE
 * Determine the direction things are going
 * where 0 is up. This returns angle (clockwise) in radians
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    / speed
 *     | a /
 *     |  /
 *     | /
 *
 *  a = atan2(dx, dy)
 *  dx = cos(a) x speed
 *  dy = sin(a) x speed
 ************************************************/
Angle Velocity::getAngle() const
{
   return Angle();
}

/*********************************************
 * VELOCITY : ADD
 * Add the velocity components of rhs to the current velocity
 *********************************************/
void Velocity::add(const Velocity & rhs)
{
   this->dx += rhs.dx;
   this->dy += rhs.dy;
}

/*********************************************
 * VELOCITY : REVERSE
 * Reverse the direction of the velocity
 *********************************************/
void Velocity::reverse()
{
   this->dx = -this->dx;
   this->dy = -this->dy;
}

int MockVelocity::defaultConstructorCalls = 0;
int MockVelocity::parameterizedConstructorCalls = 0;
int MockVelocity::copyConstructorCalls = 0;
int MockVelocity::speedAngleConstructorCalls = 0;
int MockVelocity::setAngleMagnitudeCalls = 0;
int MockVelocity::setDXCalls = 0;
int MockVelocity::setDYCalls = 0;
int MockVelocity::setSpeedCalls = 0;
int MockVelocity::setAngleCalls = 0;
int MockVelocity::addDXCalls = 0;
int MockVelocity::addDYCalls = 0;
int MockVelocity::addAccelerationCalls = 0;
int MockVelocity::addVelocityCalls = 0;
int MockVelocity::reverseCalls = 0;
