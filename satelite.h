/*****************************
 * Header File:
 *   SATELITE : The representation of a satelite
 *  Author:
 *  Br. Helfrich
 *  Summary:
 *  Everything we need to know about a satelite
 *  ******************************************/

#pragma once

#include "position.h"      // for POSITION
#include "velocity.h"      // for VELOCITY
#include "direction.h"     // for DIRECTION
#include "uiInteract.h"    // for INTERACTION
#include "uiDraw.h"        // for DRAWING
#include "physics.h"      // for all the physics stuff
#include <list>

/*************************************
   * SATELITE
 * One satelite that goes across the sky
   *************************************/
class Satelite
{
public:
   // constructors
   
   // Earth needs a default constructor
   Satelite() : angularVelocity(0.0), dead(false), age(0), radius(0.0) {}
   
   // used to create parts and fragments
   Satelite(const Satelite& parent, Direction direction) :
      velocity(parent.velocity),
      position(parent.pos),
      direction(parent.direction),
      angularVelocity(parent.angularVelocity),
      radius(0.0),
      age(0)
      dead(false)
   {
      // compute the kick
      double speed = random(1000.0, 3000.0);
      direction.rotate(random(-0.1, 0.1));
      Velocity kick(speed, direction);
      velocity += kick;
      
      // compute the offset
      Position posKick;
      posKick.setPixelsX(4.0 * sin(direction.getRadians()));
      posKick.setPixelsY(4.0 * cos(direction.getRadians()));
      pos.addMetersX(posKick.getMetersX());
      pos.addMetersY(posKick.getMetersY());
   }
   
   // Used to create projectiles. They have specific speeds
   Satelite(const Satelite& parent, const Position & offset, const Velocity & kick) :
      velocity(parent.velocity),
      pos(parent.pos),
      direction(parent.direction),
      angularVelocity(parent.angularVelocity),
      radius(0.0),
      age(0),
      dead(false)
   {
      velocity += kick;
      pos.addMetersX(offset.getMetersX());
      pos.addMetersY(offset.getMetersY());
   }
   
   // getters
   
   //Return the radius of the satellite in meters
   double getRadius() const { return radius;  }
   
   // Return whether we are dead
   bool isDead() const { return dead; }
   
   // this has got to go
   bool isInvisible() const { return age < 10; }
   
   // Where are we pointed
   const Direction& getAngle() const { return direction; }
   
   // Where we are located
   const Position& getPosition() const { return pos; }
   
   // setters
   
   virtual void kill() { if (!isInvisible()) dead = true; }
   
   // stuff to be overridden
   
   virtual bool getDefunct() { return false;   }
   
   // draw the item on the screen
   virtual void draw() {}
   
   // kill this element
   virtual void destroy(std::list <Satel)
}
 
