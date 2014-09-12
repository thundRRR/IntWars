#include "Map.h"
#include "Game.h"

void Map::update(int64 diff) {
   for(auto kv = objects.begin(); kv != objects.end();) {
      if(kv->second->isToRemove()) {
         delete kv->second;
         kv = objects.erase(kv);
         continue;
      }
      
      if(kv->second->isMovementUpdated()) {
         game->notifyMovement(kv->second);
         kv->second->clearMovementUpdated();
      }
      
      Unit* u = dynamic_cast<Unit*>(kv->second);

      if(!u) {
         kv->second->update(diff);
         ++kv;
         continue;
      }
      
      if(u->buffs.size() != 0){
    
          for(int i = u->buffs.size(); i>0;i--){

              if(u->buffs[i-1]->needsToRemove()){
                  u->buffs.erase(u->getBuffs().begin() + (i-1));
                  //todo move this to Buff.cpp and add every stat
                  u->getStats().addMovementSpeedPercentageModifier(-u->getBuffs()[i-1]->getMovementSpeedPercentModifier());
                  continue;
              }
              u->buffs[i-1]->update(diff);
          }
      }
      
      
      if(!u->getStats().getUpdatedStats().empty()) {
         game->notifyUpdatedStats(u);
         u->getStats().clearUpdatedStats();
      }
      
      if(u->getStats().isUpdatedHealth()) {
         game->notifySetHealth(u);
         u->getStats().clearUpdatedHealth();
      }
      
      if(u->isModelUpdated()) {
         game->notifyModelUpdate(u);
         u->clearModelUpdated();
      }
      
      kv->second->update(diff);
      ++kv;
   }
   
   time += diff;
   
   if(waveNumber) { 
      if(time >= nextSpawnTime+waveNumber*8*100000) { // Spawn new wave every 0.8s
         if(spawn()) {
            waveNumber = 0;
            nextSpawnTime += spawnInterval;
         } else {
            ++waveNumber;
         }
      }  
   } else if(time >= nextSpawnTime) {
      spawn();
      ++waveNumber;
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