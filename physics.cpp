/***********************************
 * Source File:
 *  Physics : Handle all the physics
 *  Author:
 *    Br. Helfrich
 *   Summary:
 *   Everything we need to know about the things in motion
   ***************************************/

#include "physics.h"
//#include "position.h"
#include <cmath>

// C++ implementation
#include <cmath>
#include "Position.h"

//// Compute the Euclidean distance between two Position objects
//double computeDistance(const Position& p1, const Position& p2) {
//    double dx = p2.getMetersX() - p1.getMetersX();
//    double dy = p2.getMetersY() - p1.getMetersY();
//    return std::sqrt(dx * dx + dy * dy);
//}

// radius of the earth is 6378km
const double earthRadiusMeters = 6378000.0;        // in meters

/***************************
 * GET ALTITUDE
   * Return the altitude of a point above the surface of the earth
   *   INPUT  POSITION   The location of the point
 *   ************************************/
double getAltitude(const Position& posElement)
{
   // Note that the earth is centered at (0,0) which is the default Position
   double distance = computeDistance(Position(), posElement);
   return distance - earthRadiusMeters;
}

/***************************
 * GET GRAVITY
 *  Return the gravity acceleration at a given point
 *
 *  Equation: a = g_0 (R_e / (R_e + h))^2
 **************************************/
Acceleration getGravity(const Position& posElement)
{
   // compute the height above the earth
   double height = getAltitude(posElement);
   
   // the direction of gravity is straight down
   Direction direction;
   direction.setDxDy(-posElement.getMetersX(), -posElement.getMetersY());
   
   // a = g_0 (R_e / (R_e + h))^2
   double standardGravity = 9.80665; // m/s^2
   double tmp = earthRadiusMeters / (earthRadiusMeters + height);
   double acceleration = standardGravity * tmp * tmp;
   
   return Acceleration(acceleration, direction);
}

/***************************
 * UPDATE VELOCITY
   * Update the current velocity
   *   INPUT         VELOCITY             The initial velocity
 *             ACCELERATION   The  acceleration acting on it
 *             TIME                       How much time are we talking about here?
 *  OUTPUT     VELOCITY            The velocity to be updated
 *
 * dx = dx + ddx t
 * dy = dy + ddy t
 * *********************************************/
Velocity& updateVelocity(Velocity& velocity, const Acceleration& acceleration, double time)
{
   velocity.addDX(acceleration.getDDX() * time);
   velocity.addDY(acceleration.getDDY() * time);
   return velocity;
}

/***************************
 * UPDATE POSITION
 *  Update the current position based on the impulse of the velocity
 *  taking into account time dilation
 *  INPUT      POSITION            The current position of the item
 *          VELOCITY            The current velocity
 *          ACCELERATION   The current acceleration
 *          TIME                       How much time are we talking about here?
 *  OUTPUT     POSITION            The position to be updated
 *
 * x = x + dx t + 0.5 ddx t^2
 * y = y + dy t + 0.5 ddy t^2
 * *********************************************/
Position& updatePosition(Position& pos, const Velocity& vel, const Acceleration& acc, double time)
{
   pos.addMetersX(vel.getDX() * time + 0.5 * acc.getDDX() * time * time);
   pos.addMetersY(vel.getDY() * time + 0.5 * acc.getDDY() * time * time);
   return pos;
}
 
