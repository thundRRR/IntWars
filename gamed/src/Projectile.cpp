#include <map>

#include "Map.h"
#include "Projectile.h"
#include "Spell.h"
#include "Unit.h"
#include "Minion.h"
#include "Turret.h"
#include "Champion.h"

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
            
            uint32 spellFlags = originSpell->getFlags();
            
            if(u->getSide() == owner->getSide() && !(spellFlags & SPELL_FLAG_AffectFriends)) {
               continue;
            }
            
            if(u->getSide() != owner->getSide() && !(spellFlags & SPELL_FLAG_AffectEnemies)) {
               continue;
            }
            
            Minion* m = dynamic_cast<Minion*>(u);
            if(m && !(spellFlags & SPELL_FLAG_AffectMinions)) {
               continue;
            }
            
            Turret* t = dynamic_cast<Turret*>(u);
            if(t && !(spellFlags & SPELL_FLAG_AffectTurrets)) {
               continue;
            }
            
            Champion* c = dynamic_cast<Champion*>(u);
            if(c && !(spellFlags & SPELL_FLAG_AffectHeroes)) {
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