/**
 * An object is an abstract entity.
 * This is the base class for units and projectiles.
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <list>

#include "Target.h"
#include "stdafx.h"

class Map;

class Object : public Target {
protected:
  	uint32 id;

	float xvector, yvector;
	Target* target;
   Map* map;

   unsigned int side;
   
   int hitboxWidth, hitboxHeight;
   
public:
	
    virtual ~Object();
    Object(Map* map, uint32 id, float x, float y, int hitboxWidth, int hitboxHeight);

    /**
    * Moves the object depending on its target, updating its coordinate.
    * @param diff the amount of milliseconds the object is supposed to move
    * @param moveSpeed the object's moveSpeed
    */
    void Move(unsigned int diff, unsigned int moveSpeed = 40);
    
    void calculateVector(float xtarget, float ytarget);

    /**
    * Sets the side (= team) of the object
    * @param side the new side
    */
    void setSide(unsigned int side) { this->side = side; }
    unsigned int getSide() { return side; }

    virtual void update(unsigned int diff) = 0;

    virtual bool isSimpleTarget() { return false; }

    Target* getTarget() { return target; }
    virtual void setTarget(Target* target);
    uint32 getNetId() const { return id; }
    Map* getMap() const { return map; }

    void setPosition(float x, float y);

    bool collide(Object* o);
    bool isPointInHitbox(float x, float y);
};

#endif /* OBJECT_H_ */
