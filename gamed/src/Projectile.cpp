#include <map>

#include "Map.h"
#include "Projectile.h"

void Projectile::update(unsigned int diff) {

   Object::update(diff);

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
         
         if(collide(it.second)) {
            printf("Collide with 0x%08X !\n", it.second->getNetId());
            originSpell->applyEffects(it.second, this);
         }
      }
   }
   
}