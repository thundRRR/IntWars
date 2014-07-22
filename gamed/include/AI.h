#ifndef _AI_H
#define _AI_H

#include "Unit.h"

class AI {

protected:
   Unit* me;
   
public:
   AI(Unit* me) : me(me) { }
   
   virtual void onSpawn() = 0;
   virtual void onDamageTaken(Unit* source, float amount) = 0;
   virtual void update(unsigned int diff) { }

};

#endif