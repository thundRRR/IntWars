#include "Unit.h"
#include "AI.h"

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