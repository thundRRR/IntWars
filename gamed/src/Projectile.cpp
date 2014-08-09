#include <map>

#include "Map.h"
#include "Projectile.h"
#include "Spell.h"
#include "Unit.h"

void Projectile::update(int64 diff) {

   if(!target) {
      setToRemove();
      return;
   }
   
   if(target->isSimpleTarget()) { // Skillshot
      const std::map<uint32, Object*>& objects = map->getObjects();
      for(auto& it : objects) {
         if(isToRemove()) {
            return;
         }
         
         if(collide(it.second) && it.second->getNetId() != getNetId()) {//projectile shouldn't collide with itself
            Unit* u = dynamic_cast<Unit*>(it.second);
            if(!u) {
               continue;
            }
            originSpell->applyEffects(u, this);
         }
      }
   } else {
      Unit* u = static_cast<Unit*>(target);
      if(collide(u)) { // Autoguided spell
         if(originSpell) {
            originSpell->applyEffects(u, this);
         } else { // auto attack
            owner->autoAttackHit(u);
            setToRemove();
         }
      }
   }
   
   Object::update(diff);
   
}