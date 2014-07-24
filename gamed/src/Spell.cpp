#include "Spell.h"

/**
 * Called when the character casts the spell
 */
bool Spell::cast(float x, float y, Unit* u) {
   state = STATE_CASTING;
   currentCastTime = castTime;
   
   this->x = x;
   this->y = y;
   this->target = u;
   
   return true;
}

/**
 * Called when the spell is finished casting and we're supposed to do things
 * such as projectile spawning, etc.
 */
void Spell::finishCasting() {
   state = STATE_COOLDOWN;
   currentCooldown = getCooldown();
}

/**
 * Called every diff milliseconds to update the spell
 */
void Spell::update(unsigned int diff) {
   switch(state) {
      case STATE_READY:
         return;
      case STATE_CASTING:
         currentCastTime -= diff/1000.f;
         if(currentCastTime < 0) {
            finishCasting();
         }
         break;
      case STATE_COOLDOWN:
         currentCooldown -= diff/1000.f;
         if(currentCooldown < 0) {
            state = STATE_READY;
         }
         break;
   }
}