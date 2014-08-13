#include "Unit.h"
#include "AI.h"
#include "Map.h"
#include "Game.h"

#include <algorithm>

using namespace std;

Unit::~Unit() {
   delete stats;
   if(ai) {
      delete ai;
   }
}

void Unit::update(int64 diff) {
   if(isAttacking) {
      autoAttackCurrentDelay += diff/1000000.f;
      if(autoAttackCurrentDelay >= autoAttackDelay) {
         Projectile* p = new Projectile(map, autoAttackProjId, x, y, 5, this, unitTarget, 0, autoAttackProjectileSpeed, RAFFile::getHash("EzrealMysticShotMissile"));
         map->addObject(p);
         autoAttackCurrentCooldown = 1.f/(stats->getTotalAttackSpeed());
         isAttacking = false;
      }
   }
   else if(unitTarget && distanceWith(unitTarget) <= stats->getRange()) {
      if(autoAttackCurrentCooldown <= 0) {
         isAttacking = true;
         autoAttackCurrentDelay = 0;
         autoAttackProjId = GetNewNetID();
         map->getGame()->notifyAutoAttack(this, unitTarget, autoAttackProjId);
      }
   }
   else {
      Object::update(diff);
   }
   
   if(autoAttackCurrentCooldown > 0) {
      autoAttackCurrentCooldown -= diff/1000000.f;
   }
   
   if(ai) {
      ai->update(diff);
   }
   
   statUpdateTimer += diff;
   if(statUpdateTimer >= 500000) { // update stats (hpregen, manaregen) every 0.5 seconds
      stats->update(statUpdateTimer);
      statUpdateTimer = 0;
   }
}

void Unit::autoAttackHit(Unit* target) {
   dealDamageTo(target, stats->getTotalAd(), DAMAGE_TYPE_PHYSICAL, DAMAGE_SOURCE_ATTACK);
}

/**
 * TODO : handle armor, magic resistance [...]
 */
void Unit::dealDamageTo(Unit* target, float damage, DamageType type, DamageSource source) {
   printf("0x%08X deals %f damage to 0x%08X !\n", getNetId(), damage, target->getNetId());
   target->getStats().setCurrentHealth(max(0.f, target->getStats().getCurrentHealth()-damage));
   map->getGame()->notifyDamageDone(this, target, damage);
}

bool Unit::isDead() const {
   return stats->getCurrentHealth() <= 0;
}

void Unit::setModel(const std::string& newModel) {
    model = newModel;
    modelUpdated = true;
}

const std::string& Unit::getModel() {
    return model;
}