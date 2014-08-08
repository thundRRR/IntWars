#ifndef _MAP_H
#define _MAP_H

#include <map>
#include <vector>

#include "stdafx.h"
#include "Object.h"

class Game;

class Map {

protected:
   std::map<uint32, Object*> objects;
   std::vector<uint32> expToLevelUp;
   Game* game;
   
public:
   Map(Game* game) : game(game) { }
   
   virtual ~Map() { }
   virtual void update(long long diff);
   virtual float getGoldPerSecond() = 0;
   
   Object* getObjectById(uint32 id);
   void addObject(Object* o);
   const std::vector<uint32>& getExpToLevelUp() { return expToLevelUp; }
   
   Game* getGame() const { return game; }
   
   const std::map<uint32, Object*>& getObjects() { return objects; }

};

#endif