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
   
   autoAttackDelay = 4.95/30;
   autoAttackProjectileSpeed = 1200;
   
   setSide(side);
}

void Turret::update(int64 diff)
{
   // No target : try to find a new one
   if(!isAttacking && autoAttackCurrentCooldown <= 0 && !unitTarget) {
      const std::map<uint32, Object*>& objects = map->getObjects();

      for(auto& it : objects) {
         Unit* u = dynamic_cast<Unit*>(it.second);

         if(!u || u->isDead() || u->getSide() == getSide() || distanceWith(u) > TURRET_RANGE) {
            continue;
         }

         unitTarget = u;
         map->getGame()->notifySetTarget(this, u);
         break;
      }
   } else if(unitTarget && distanceWith(unitTarget) > TURRET_RANGE) {
      setUnitTarget(0);
   }

   Unit::update(diff);
}