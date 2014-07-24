#include <map>

#include "Map.h"
#include "Projectile.h"

void Projectile::update(int64 diff) {

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
         
         printf("Checking with 0x%08X (%f ; %f) !\n", it.second->getNetId(), it.second->getX(), it.second->getY());
         
         if(collide(it.second)) {
            printf("Collide with 0x%08X !\n", it.second->getNetId());
            originSpell->applyEffects(it.second, this);
         }
      }
   }
   
}