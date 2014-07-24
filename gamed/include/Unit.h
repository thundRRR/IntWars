#ifndef _UNIT_H
#define _UNIT_H

#include "Object.h"
#include "Stats.h"

enum DamageType {
   DAMAGE_TYPE_PHYSICAL,
   DAMAGE_TYPE_MAGICAL
};

enum DamageSource {
   DAMAGE_SOURCE_ATTACK,
   DAMAGE_SOURCE_SPELL
};

class AI;

class Unit : public Object {

protected:
   Stats* stats;
   AI* ai;

public:
   Unit(Map* map, uint32 id, Stats* stats, float x = 0, float y = 0, AI* ai = 0) : Object(map, id, x, y, 40, 40), stats(stats), ai(ai) { }
   virtual ~Unit();
   Stats& getStats() { return *stats; }
   virtual void update(int64 diff);
   virtual float getMoveSpeed() const { return stats->getMovementSpeed(); }
   
   void dealDamageTo(Unit* target, float damage, DamageType type, DamageSource source);

};

#endif