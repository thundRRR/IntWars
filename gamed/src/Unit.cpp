#include "Unit.h"
#include "AI.h"
#include "Map.h"
#include "Game.h"

#include <algorithm>

#define DETECT_RANGE 400

using namespace std;

Unit::~Unit() {
    delete stats;
    if (ai) {
        delete ai;
    }
}

void Unit::update(int64 diff) {

      if(unitScript.isLoaded()){
   try{
   unitScript.lua.get <sol::function> ("onUpdate").call <void> (diff);
   }catch(sol::error e){
      printf("%s", e.what());
   }
   }

   if (isDead()) {
   return;
   }

   if (unitTarget && unitTarget->isDead()) {
      setUnitTarget(0);
      isAttacking = false;
      map->getGame()->notifySetTarget(this, 0);
   }
   
   if(!unitTarget && isAttacking) {
      isAttacking = false;
   }

   if (isAttacking) {
      autoAttackCurrentDelay += diff / 1000000.f;
      if (autoAttackCurrentDelay >= autoAttackDelay) {
         if(!isMelee()) {
            Projectile* p = new Projectile(map, autoAttackProjId, x, y, 5, this, unitTarget, 0, autoAttackProjectileSpeed, 0);
            map->addObject(p);
            map->getGame()->notifyShowProjectile(p);
         } else {
            autoAttackHit(unitTarget);
         }
         autoAttackCurrentCooldown = 1.f / (stats->getTotalAttackSpeed());
         isAttacking = false;
      }
   } else if (unitTarget && distanceWith(unitTarget) <= stats->getRange()) {
      refreshWaypoints();
      if (autoAttackCurrentCooldown <= 0) {
         isAttacking = true;
         autoAttackCurrentDelay = 0;
         autoAttackProjId = GetNewNetID();
         autoAttackFlag = true;
         if(!isMelee()) {
            map->getGame()->notifyAutoAttack(this, unitTarget, autoAttackProjId);
         } else {
            map->getGame()->notifyAutoAttackMelee(this, unitTarget, autoAttackProjId);
         }
      }
   } else {
      refreshWaypoints();
      if (moveOrder == MOVE_ORDER_ATTACKMOVE && !unitTarget) {
         const std::map<uint32, Object*>& objects = map->getObjects();

         for (auto& it : objects) {
            Unit* u = dynamic_cast<Unit*> (it.second);

            if (!u || u->isDead() || u->getSide() == getSide() || distanceWith(u) > DETECT_RANGE) {
               continue;
            }

            setUnitTarget(u);
            map->getGame()->notifySetTarget(this, u);

            break;
         }
      }

      Object::update(diff);
   }

   if (autoAttackCurrentCooldown > 0) {
      autoAttackCurrentCooldown -= diff / 1000000.f;
   }

   if (ai) {
      ai->update(diff);
   }

   statUpdateTimer += diff;
   if (statUpdateTimer >= 500000) { // update stats (hpregen, manaregen) every 0.5 seconds
      stats->update(statUpdateTimer);
      statUpdateTimer = 0;
   }
}

void Unit::autoAttackHit(Unit* target) {
    dealDamageTo(target, stats->getTotalAd(), DAMAGE_TYPE_PHYSICAL, DAMAGE_SOURCE_ATTACK);
       if(unitScript.isLoaded()){
      try{
         unitScript.lua.get <sol::function> ("onAutoAttack").call <void> (target);
      }catch(sol::error e){
         printf("Error callback ondealdamage: \n%s", e.what());
      }
   }
}

/**
 * TODO : handle armor, magic resistance [...]
 */
void Unit::dealDamageTo(Unit* target, float damage, DamageType type, DamageSource source) {
    //printf("0x%08X deals %f damage to 0x%08X !\n", getNetId(), damage, target->getNetId());
    
   if(unitScript.isLoaded()){
      try{
         /*damage = */ unitScript.lua.get <sol::function> ("onDealDamage").call <void> (target, damage, type, source);
      }catch(sol::error e){
         printf("Error callback ondealdamage: \n%s", e.what());
      }
   }
    
    
    float defense = 0;
    float regain = 0;
    switch (type) {
        case DAMAGE_TYPE_PHYSICAL:
            defense = target->getStats().getArmor();
            defense = ((1 - stats->getArmorPenPct()) * defense) - stats->getArmorPenFlat();
            
            break;
        case DAMAGE_TYPE_MAGICAL:
            defense = target->getStats().getMagicArmor();
            defense = ((1 - stats->getMagicPenPct()) * defense) - stats->getMagicPenFlat();
            break;
    }
    
    switch(source) {
        case DAMAGE_SOURCE_SPELL:
            regain = stats->getSpellVamp();
            break;
        case DAMAGE_SOURCE_ATTACK:
            regain = stats->getLifeSteal();
            break;
    }
    
    //Damage dealing. (based on leagueoflegends' wikia)
    damage = defense >= 0 ? (100 / (100 + defense)) * damage : (2 - (100 / (100 - defense))) * damage;

    target->getStats().setCurrentHealth(max(0.f, target->getStats().getCurrentHealth() - damage));
    if (!target->deathFlag && target->getStats().getCurrentHealth() <= 0) {
        target->deathFlag = true;
        target->die(this);
    }
    map->getGame()->notifyDamageDone(this, target, damage, type);
    
    //Get health from lifesteal/spellvamp
    if (regain != 0) {
        stats->setCurrentHealth (max (0.f, stats->getCurrentHealth() + (regain * damage)));
    }
}

bool Unit::isDead() const {
    return deathFlag;
}

void Unit::setModel(const std::string& newModel) {
    model = newModel;
    modelUpdated = true;
}

const std::string& Unit::getModel() {
    return model;
}

void Unit::die(Unit* killer) {
    map->getGame()->notifyNpcDie(this, killer);
    Champion* c = dynamic_cast<Champion*>(killer);
    
    if(!c) {
      return;
    }
    
    float gold = map->getGoldFor(this);
    
    if(!gold) {
      return;
    }
    
    c->getStats().setGold(c->getStats().getGold()+gold);
    map->getGame()->notifyAddGold(c, this, gold);
    setToRemove();
    map->stopTargeting(this);
}

void Unit::setUnitTarget(Unit* target) {
   unitTarget = target;
   refreshWaypoints();
}

void Unit::refreshWaypoints() {
   if (!unitTarget || (distanceWith(unitTarget) <= stats->getRange() && waypoints.size() == 1)) {
      return;
   }

   if (distanceWith(unitTarget) <= stats->getRange()-2.f) {
      setWaypoints({MovementVector(x, y)});
   } else {
      Target* t = waypoints[waypoints.size()-1].toTarget();
      if(t->distanceWith(unitTarget) >= 25.f) {
         setWaypoints({MovementVector(x, y), MovementVector(unitTarget->getX(), unitTarget->getY())});
      }
      delete t;
   }
}

Buff* Unit::getBuff(std::string name){
   for(auto& buff : buffs){
      if(buff->getName() == name){
         return buff;
       }
   }
   return 0;
}
