#include "Unit.h"
#include "AI.h"

#include <algorithm>

using namespace std;

Unit::~Unit() {
   delete stats;
   if(ai) {
      delete ai;
   }
}

void Unit::update(unsigned int diff) {
   Object::update(diff);
   
   if(ai) {
      ai->update(diff);
   }
}

void Unit::dealDamageTo(Unit* target, float damage, DamageType type, DamageSource source) {
   target->getStats().setCurrentHealth(max(0.f, target->getStats().getCurrentHealth()-damage));
}