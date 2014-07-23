#include "Map.h"
#include "Game.h"

void Map::update(unsigned int diff) {
   for(auto& kv : objects) {
      kv.second->update(diff);
      
      if(kv.second->isMovementUpdated()) {
         game->notifyMovement(kv.second);
         kv.second->clearMovementUpdated();
      }
      
      Unit* u = dynamic_cast<Unit*>(kv.second);
      
      if(u && !u->getStats().getUpdatedStats().empty()) {
         game->notifyUpdatedStats(u);
         u->getStats().clearUpdatedStats();
      }
   }
}

Object* Map::getObjectById(uint32 id) {
   if(objects.find(id) == objects.end()) {
      return 0;
   }
   
   return objects[id];
}

void Map::addObject(Object* o) {
   objects[o->getNetId()] = o;
}