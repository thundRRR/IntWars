#ifndef _MINION_AI_H
#define _MINION_AI_H

#include "AI.h"

class MinionAI : public AI {
   
public:
   MinionAI(Unit* me) : AI(me) { }
   void update(unsigned int diff) { }
   void onSpawn() { }
   void onDamageTaken(Unit* source, float amount) { }

};

#endif