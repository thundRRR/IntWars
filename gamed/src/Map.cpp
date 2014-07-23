#include "Map.h"
#include "Game.h"

void Map::update(unsigned int diff) {
   for(std::map<uint32, Object*>::iterator kv = objects.begin(); kv != objects.end();) {
      kv->second->update(diff);
      
      if(kv->second->isMovementUpdated()) {
         game->notifyMovement(kv->second);
         kv->second->clearMovementUpdated();
      }
      
      Unit* u = dynamic_cast<Unit*>(kv->second);
      
      if(u && !u->getStats().getUpdatedStats().empty()) {
         game->notifyUpdatedStats(u);
         u->getStats().clearUpdatedStats();
      }
      
      if(u && u->getStats().isUpdatedHealth()) {
         game->notifySetHealth(u);
         u->getStats().clearUpdatedHealth();
      }
      
      if(kv->second->isToRemove()) {
         delete kv->second;
         kv = objects.erase(kv);
      } else {
         ++kv;
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