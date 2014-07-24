#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <vector>

#include "Object.h"

class Spell;

class Projectile : public Object {

protected:
   std::vector<Object*> objectsHit;
   Spell* originSpell;
   float moveSpeed;

public:
   Projectile(Map* map, uint32 id, float x, float y, int hitboxWidth, int hitboxHeight, Target* target, Spell* originSpell, float moveSpeed) : Object(map, id, x, y, hitboxWidth, hitboxHeight), originSpell(originSpell), moveSpeed(moveSpeed) {
      setTarget(target);
   }
   
   void update(unsigned int diff);
   float getMoveSpeed() const { return moveSpeed; }

   


};

#endif