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
   uint32 projectileId;
   uint32 flags;

public:
   Projectile(Map* map, uint32 id, float x, float y, uint32 collisionRadius, Unit* owner, Target* target, Spell* originSpell, float moveSpeed, uint32 projectileId, uint32 flags = 0) : Object(map, id, x, y, collisionRadius), originSpell(originSpell), moveSpeed(moveSpeed), owner(owner), projectileId(projectileId), flags(flags) {
      setTarget(target);
   }
   
   void update(int64 diff) override;
   float getMoveSpeed() const { return moveSpeed; }
   Unit* getOwner() const { return owner; }
   const std::vector<Object*>& getObjectsHit() { return objectsHit; };
   
   uint32 getProjectileId() const { return projectileId;}
   

};

#endif