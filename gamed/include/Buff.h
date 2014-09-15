#ifndef BUFF_H
#define BUFF_H

#include "stdafx.h"
#include <string>

class Unit;

class Buff{
protected:
   float duration;
   float movementSpeedPercentModifier = 0.0f;
   float timeElapsed = 0.0f;
   bool remove = false;
   Unit* attachedTo;
   std::string name = "";

public:

   Unit* const getUnit(){
   return attachedTo;
   }
   
   void setName(std::string naame){
   name = naame;
   }
   
    
   bool needsToRemove() { return remove; }
   Buff(std::string buffName, float dur, Unit* u);

   float getMovementSpeedPercentModifier() { return movementSpeedPercentModifier;}

   void setMovementSpeedPercentModifier(float modifier){ movementSpeedPercentModifier = modifier; }
   
   std::string const getName(){
   return name;
   }
   

   void update(int64 diff);
};


#endif	/* BUFF_H */

