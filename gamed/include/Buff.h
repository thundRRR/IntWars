#ifndef BUFF_H
#define BUFF_H

#include "stdafx.h"
#include <string>

class Unit;

class Buff{
protected:
   float duration;
   float movementSpeedPercentModifier;
   float timeElapsed;
   bool remove = false;
   Unit* attachedTo;
   std::string name;

public:

   Unit* const getUnit(){
      return attachedTo;
   }
   
   void setName(const std::string& name){
      this->name = name;
   }
   
    
   bool needsToRemove() { return remove; }
   Buff(const std::string& buffName, float dur, Unit* u);

   float getMovementSpeedPercentModifier() { return movementSpeedPercentModifier;}

   void setMovementSpeedPercentModifier(float modifier){ movementSpeedPercentModifier = modifier; }
   
   std::string getName() const {
      return name;
   }
   

   void update(int64 diff);
};


#endif	/* BUFF_H */

