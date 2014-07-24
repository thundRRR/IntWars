/**
 * An object is an abstract entity.
 * This is the base class for units and projectiles.
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>

#include "Target.h"
#include "stdafx.h"

class Map;

#define MAP_WIDTH (13982 / 2)
#define MAP_HEIGHT (14446 / 2)

struct MovementVector {
    short x;
    short y;
    
    MovementVector() : x(0), y(0){ }
    MovementVector(uint16 x, uint16 y) : x(x), y(x) { }
    Target* toTarget() { return new Target(2.0*x + MAP_WIDTH, 2.0*y + MAP_HEIGHT); }
};

class Object : public Target {
protected:
  	uint32 id;

	float xvector, yvector;
	Target* target;
   std::vector<MovementVector> waypoints;
   uint32 curWaypoint;
   Map* map;

   unsigned int side;
   bool movementUpdated;
   bool toRemove;
   
   int hitboxWidth, hitboxHeight;
   
public:
	
    virtual ~Object();
    Object(Map* map, uint32 id, float x, float y, int hitboxWidth, int hitboxHeight);

    /**
    * Moves the object depending on its target, updating its coordinate.
    * @param diff the amount of milliseconds the object is supposed to move
    */
    void Move(unsigned int diff);
    
    void calculateVector(float xtarget, float ytarget);

    /**
    * Sets the side (= team) of the object
    * @param side the new side
    */
    void setSide(unsigned int side) { this->side = side; }
    unsigned int getSide() { return side; }

    virtual void update(unsigned int diff);
    virtual float getMoveSpeed() const = 0;

    virtual bool isSimpleTarget() { return false; }

    Target* getTarget() { return target; }
    void setTarget(Target* target);
    void setWaypoints(const std::vector<MovementVector>& waypoints);
    
    const std::vector<MovementVector>& getWaypoints() { return waypoints; }
    bool isMovementUpdated() { return movementUpdated; }
    void clearMovementUpdated() { movementUpdated = false; }
    bool isToRemove() { return toRemove; }
    void setToRemove() { toRemove = true; }
    
    uint32 getNetId() const { return id; }
    Map* getMap() const { return map; }

    void setPosition(float x, float y);

    bool collide(Object* o);
    bool isPointInHitbox(float x, float y);
};

#endif /* OBJECT_H_ */
