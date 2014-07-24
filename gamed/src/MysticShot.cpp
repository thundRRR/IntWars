#include "Champions/Ezreal/MysticShot.h"

#include "Game.h"
#include "Map.h"

/**
 * This is called when the spell is finished casting, and we're supposed to
 * create the projectile
 */
void MysticShot::finishCasting() {
   Spell::finishCasting();

   Map* m = owner->getMap();
   
   Projectile* p = new Projectile(owner->getMap(), GetNewNetID(), owner->getX(), owner->getY(), 60, 30, new Target(x, y), this, 2000.f);
   owner->getMap()->addObject(p);
}

/**
 * This will be called when Mystic's Shot projectile hits a unit
 */
void MysticShot::applyEffects(Target* t, Projectile* p) {
   if(!p) {
      return;
   }
   
   Unit* u = dynamic_cast<Unit*>(t);
   if(!u) {
      return;
   }
   
   if(u->getSide() == owner->getSide()) {
      return;
   }
   
   owner->dealDamageTo(u, damage[level-1], DAMAGE_TYPE_PHYSICAL, DAMAGE_SOURCE_SPELL);
   
   p->setToRemove();
}