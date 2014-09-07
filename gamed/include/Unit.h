#ifndef _UNIT_H
#define _UNIT_H

#include "Object.h"
#include "Stats.h"
#include <string>
#include "Buff.h"

enum DamageType {
   DAMAGE_TYPE_PHYSICAL,
   DAMAGE_TYPE_MAGICAL
};

enum DamageSource {
   DAMAGE_SOURCE_ATTACK,
   DAMAGE_SOURCE_SPELL
};

enum MoveOrder {
   MOVE_ORDER_MOVE,
   MOVE_ORDER_ATTACKMOVE
};

class AI;

class Unit : public Object {

protected:
   Stats* stats;
   AI* ai;
   float autoAttackDelay, autoAttackProjectileSpeed;
   float autoAttackCurrentCooldown, autoAttackCurrentDelay;
   bool isAttacking, modelUpdated;
   uint64 statUpdateTimer;
   uint32 autoAttackProjId;
   MoveOrder moveOrder;
   
   std::string model;
   
public:
   Unit(Map* map, uint32 id, std::string model, Stats* stats, uint32 collisionRadius = 40, float x = 0, float y = 0, AI* ai = 0) : Object(map, id, x, y, collisionRadius), stats(stats), ai(ai),
                                                                                 statUpdateTimer(0), model(model), autoAttackDelay(0), autoAttackProjectileSpeed(0), isAttacking(false),
                                                                                 autoAttackCurrentCooldown(0), autoAttackCurrentDelay(0), modelUpdated(false), moveOrder(MOVE_ORDER_MOVE) { }
   virtual ~Unit();
   Stats& getStats() { return *stats; }
   virtual void update(int64 diff) override;
   virtual float getMoveSpeed() const {stats->getMovementSpeed(); 
   }
   
   std::vector<Buff*> buffs;  
   
   std::vector<Buff*>& getBuffs() { return buffs;}
   
   /**
    * This is called by the AA projectile when it hits its target
    */
   virtual void autoAttackHit(Unit* target);
   
   void dealDamageTo(Unit* target, float damage, DamageType type, DamageSource source);
   
   bool isDead() const;
      
   void setModel(const std::string& newModel);
   const std::string& getModel();
   bool isModelUpdated() { return modelUpdated; }
   void clearModelUpdated() { modelUpdated = false; }
   void addBuff(Buff* b){buffs.push_back(b);}
   void setMoveOrder(MoveOrder moveOrder) { this->moveOrder = moveOrder; }
};

#endif