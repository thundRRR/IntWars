#ifndef _SPELL_MYSTICSHOT_H
#define _SPELL_MYSTICSHOT_H

#include "Spell.h"
#define ID_MYSTICSHOT 0x017f4044

class MysticShot : public Spell {
public:
   MysticShot(Champion* owner) : Spell(ID_MYSTICSHOT, owner, 0.25f, 0) {
      cooldown[0] = 6;
      cooldown[1] = 5.5f;
      cooldown[2] = 5;
      cooldown[3] = 4.5f;
      cooldown[4] = 4;
      
      cost[0] = 28;
      cost[1] = 31;
      cost[2] = 34;
      cost[3] = 37;
      cost[4] = 40;
   }
   
   /**
    * TODO : create the projectile here, and notify it to the map/game
    */
   virtual bool cast(float x, float y, Unit* u = 0) {
      return Spell::cast(x, y, u);
   }
   
   /**
    * This is called when the spell is finished casting, and we're supposed to
    * create the projectile
    */
   virtual void finishCasting() {
      Spell::finishCasting();
   }
   
   /**
    * This will be called when Mystic's Shot projectile hits a unit
    */
   virtual void applyEffects(float x, float y, Unit* u = 0) {
   
   }


};

#endif