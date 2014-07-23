#include "Object.h"
#include <cmath>

using namespace std;

Object::Object(Map* map, uint32 id, float x, float y, int hitboxWidth, int hitboxHeight) : Target(x, y), map(map), id(id), target(0), hitboxWidth(hitboxWidth), hitboxHeight(hitboxHeight), movementUpdated(false) {
}

Object::~Object() {

}

void Object::calculateVector(float xtarget, float ytarget) {
   xvector = xtarget-x;
   yvector = ytarget-y;

   if(xvector == 0 && yvector == 0)
    return;

   float tmp = std::max(abs(xvector), abs(yvector));
   xvector /= tmp;
   yvector /= tmp;
}

void Object::setTarget(Target* target) {
   if(this->target == target)
      return;

   if(this->target && this->target->isSimpleTarget()) {
      delete this->target;
   }
      
   this->target = target;

}

void Object::Move(unsigned int diff) {

	if(!target)
	  return;
	
	calculateVector(target->getX(), target->getY());

	float factor = 0.001f*diff*getMoveSpeed();

	x += factor*xvector;
	y += factor*yvector;
	
	/* If the target was a simple point, stop when it is reached */
	if(target->isSimpleTarget() && distanceWith(target) < factor) {
	   if(++curWaypoint >= waypoints.size()) {
         setTarget(0);
      } else {
         setTarget(waypoints[curWaypoint].toTarget());
      }
	}
}

void Object::update(unsigned int diff) {
   Move(diff);
}

void Object::setWaypoints(const std::vector<MovementVector>& newWaypoints) {
   waypoints = newWaypoints;
   
   setPosition(2.0 * waypoints[0].x + MAP_WIDTH, 2.0 * waypoints[0].y + MAP_HEIGHT);
   movementUpdated = true;
   if(waypoints.size() == 1) {
      setTarget(0);
      return;
   }
   
   setTarget(waypoints[1].toTarget());
   curWaypoint = 1;
}

void Object::setPosition(float x, float y) {

   this->x = x;
   this->y = y;

   setTarget(0);
}

bool Object::collide(Object* o) {
   float minX = o->x - o->hitboxWidth/2;
   float maxX = o->x + o->hitboxWidth/2;
   float minY = o->y - o->hitboxHeight/2;
   float maxY = o->y + o->hitboxHeight/2;

   if (  isPointInHitbox(minX, minY   ) ||
         isPointInHitbox(minX, maxY   ) ||
         isPointInHitbox(maxX, minY   ) ||
         isPointInHitbox(maxX, maxY   )
      )
        return true;
        
   minX = this->x - hitboxWidth/2;
   maxX = this->x + hitboxWidth/2;
   minY = this->y - hitboxHeight/2;
   maxY = this->y + hitboxHeight/2;
   
   if (  o->isPointInHitbox(minX, minY   ) ||
         o->isPointInHitbox(minX, maxY   ) ||
         o->isPointInHitbox(maxX, minY   ) ||
         o->isPointInHitbox(maxX, maxY   )
      )
        return true;
    
   return false;
}

bool Object::isPointInHitbox(float x, float y) {
   float minX = this->x - hitboxWidth/2;
   float maxX = this->x + hitboxWidth/2;
   float minY = this->y - hitboxHeight/2;
   float maxY = this->y + hitboxHeight/2;

   if ((minX  <= x && x <= maxX) && (minY <= y && y <= maxY))
        return true;
        
    return false;
}