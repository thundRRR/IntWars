#include "Map.h"

void Map::update(unsigned int diff) {
   for(auto& kv : objects) {
      kv.second->update(diff);
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