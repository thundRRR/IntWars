#ifndef _SPELL_MYSTICSHOT_H
#define _SPELL_MYSTICSHOT_H

#include "Spell.h"
#define ID_MYSTICSHOT 0x017f4044

class MysticShot : public Spell {
public:
   MysticShot(Champion* owner) : Spell(ID_MYSTICSHOT, owner, 0.25f) {
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
   virtual bool cast(float x, float y, Object* o = 0) {
   
   }




};

#endif