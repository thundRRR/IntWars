#include "Unit.h"
#include "AI.h"

void Unit::update(unsigned int diff) {
   if(ai) {
      ai->update(diff);
   }
}