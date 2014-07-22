#include "Minion.h"

Minion::Minion(Map* map, uint32 id, MinionSpawnType type, MinionSpawnPosition position) : Unit(map, id, 0, 0, new MinionAI(this)), type(type), position(position) {
   switch(position) {
   case SPAWN_BLUE_TOP:
      setSide(0);
      // setPosition(x, y);
      break;
   case SPAWN_BLUE_BOT:
      setSide(0);
      // setPosition(x, y);
      break;
   case SPAWN_BLUE_MID:
      setSide(0);
      // setPosition(x, y);
      break;
   case SPAWN_RED_TOP:
      setSide(1);
      // setPosition(x, y);
      break;
   case SPAWN_RED_BOT:
      setSide(1);
      // setPosition(x, y);
      break;
   case SPAWN_RED_MID:
      setSide(1);
      // setPosition(x, y);
      break;
   }
   
   switch(type) {
   case MINION_TYPE_MELEE:
      stats.setCurrentHealth(475.0f);
      stats.setMaxHealth(475.0f);
      break;
   case MINION_TYPE_CASTER:
      stats.setCurrentHealth(279.0f);
      stats.setMaxHealth(279.0f);
      break;
   case MINION_TYPE_CANNON:
      stats.setCurrentHealth(600.0f);
      stats.setMaxHealth(600.0f);
      break;
   }
}