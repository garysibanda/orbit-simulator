/***********************************
 * Header File:
 *   PHYSICS : Handle all the physics
 * Author:
 *  Br. Helfrich, Gary Sibanda
 * Summary:
 *  Everything we need to know about the things in motion
 ***************************************/

#pragma once

#include <cmath>        // for SQRT
#include "position.h"
#include "velocity.h"

/*********************************************
 * GET ALTITUDE
 * Return the altitude of a point above the surface of the earth
 *   INPUT  POSITION   The location of the point
 *********************************************/
double getAltitude(const Position& posElement);

/*********************************************
 * GET GRAVITY
 *  Return the gravity acceleration at a given point
 *  INPUT  POSITION   The location of the point
 *
 *  Equation: a = g_0 (R_e / (R_e + h))^2
 **********************************************/
Acceleration getGravity(const Position& posElement);

/*********************************************
 * UPDATE VELOCITY
 * Update the current velocity
 *   INPUT      VELOCITY            The current velocity
 *          ACCELERATION   The current acceleration
 *          TIME                       How much time are we talking about here?
 *  OUTPUT     VELOCITY            The velocity to be updated
 *
 * dx = dx + ddx t
 *  dy = dy + ddy t
 *  *********************************************/
Velocity& updateVelocity(Velocity& velocity, const Acceleration& accelration, double time);

/*********************************************
   * UPDATE POSITION
   * Update the current position based on the impulse of the velocity
 * taking into account time dilation
 *  INPUT      POSITION            The current position of the item
   *          VELOCITY            The current velocity
   *          ACCELERATION   The current acceleration
   *          TIME                       How much time are we talking about here?
   *  OUTPUT     POSITION            The position to be updated
   *
   * x = x + dx t + 0.5 ddx t^2
   *  y = y + dy t + 0.5 ddy t^2
   *  *********************************************/
Position& updatePosition(Position& pos, const Velocity& vel, const Acceleration& acc, double time);
 
// physics.h
double computeDistance(const Position& p1, const Position& p2);
