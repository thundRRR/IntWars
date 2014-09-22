#include "Turret.h"
#include "Map.h"
#include "TurretStats.h"
#include "Game.h"

#define TURRET_RANGE 775

Turret::Turret(Map* map, uint32 id, const std::string& name, float x, float y, float hp, float ad, int side) : Unit(map, id, "", new TurretStats(), 50, x, y, 0), name(name)  {
   stats->setCurrentHealth(hp);
   stats->setMaxHealth(hp);
   stats->setBaseAd(ad);
   stats->setRange(TURRET_RANGE);
   
   autoAttackDelay = 4.95f/30.f;
   autoAttackProjectileSpeed = 1200.f;
   
   setSide(side);
}

void Turret::update(int64 diff)
{
   // No target : try to find a new one
   if(!isAttacking && !unitTarget) {
      const std::map<uint32, Object*>& objects = map->getObjects();
      Unit* nextTarget;
      unsigned int nextTargetPriority = 10;
      for(auto& it : objects) {
         Unit* u = dynamic_cast<Unit*>(it.second);

         if(!u || u->isDead() || u->getSide() == getSide() || distanceWith(u) > TURRET_RANGE) {
            continue;
         }
         auto priority = classifyTarget(u);
         if (priority < nextTargetPriority) {
            nextTarget = u;
            nextTargetPriority = priority;
         }
      }
      if (nextTarget) {
         unitTarget = nextTarget;
         map->getGame()->notifySetTarget(this, nextTarget);
      }
   } else if(unitTarget && distanceWith(unitTarget) > TURRET_RANGE) {
      setUnitTarget(0);
      map->getGame()->notifySetTarget(this, 0);
   }

   Unit::update(diff);
}
//Prioritize targets
unsigned int Turret::classifyTarget(Unit* u) {
   Minion* m = dynamic_cast<Minion*>(u);

   if (m) {
      switch (m->getType()) {
         case MINION_TYPE_MELEE:
            return 4;
         case MINION_TYPE_CASTER:
            return 5;
         case MINION_TYPE_CANNON:
         case MINION_TYPE_SUPER:
            return 3;
      }
   }

   Champion* c = dynamic_cast<Champion*>(u);
   if (c) {
      return 6;
   }

   //Trap (Shaco box) return 1
   //Pet (Tibbers) return 2

   return 10;
}