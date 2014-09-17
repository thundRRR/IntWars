#include "Unit.h"
#include "Game.h"
#include "Buff.h"


void Buff::update(int64 diff){
   timeElapsed += (float)diff/1000000.0f;
   if(timeElapsed >= duration){
      if(name != ""){ // empty name = no buff icon
         attachedTo->getMap()->getGame()->notifyRemoveBuff(attachedTo, name);
      }
    remove = true;

   }
}

Buff::Buff(const std::string& buffName, float dur, Unit* u)  : duration(dur),  name(buffName), timeElapsed(0), remove(false), attachedTo(u), movementSpeedPercentModifier(0){
   if(name != ""){ // empty name = no buff icon
      attachedTo->getMap()->getGame()->notifyAddBuff(attachedTo, name);
   }


}

