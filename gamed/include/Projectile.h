#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <vector>

#include "Object.h"

class Spell;

class Projectile : public Object {

protected:
   std::vector<Object*> objectsHit;
   Spell* originSpell;
   Unit* owner;
   float moveSpeed;

public:
   Projectile(Map* map, uint32 id, float x, float y, int hitboxWidth, int hitboxHeight, Unit* owner, Target* target, Spell* originSpell, float moveSpeed) : Object(map, id, x, y, hitboxWidth, hitboxHeight), originSpell(originSpell), moveSpeed(moveSpeed), owner(owner) {
      setTarget(target);
   }
   
   void update(int64 diff) override;
   float getMoveSpeed() const { return moveSpeed; }

};

#endif