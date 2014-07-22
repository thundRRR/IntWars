#ifndef __H_STATS
#define __H_STATS

#include <map>
#include <set>

#include "stdafx.h"

class Stats {

private:
   std::map<uint32, float> stats[5];
   std::set<std::pair<uint8, uint32> > updatedStats;
   
public:
   float getStat(uint8 blockId, uint32 stat) const;
   float setStat(uint8 blockId, uint32 stat, float value);
   
   float getCurrentHealth() const;
   float getMaxHealth() const;
   void setCurrentHealth(float health);
   void setMaxHealth(float health);

};

#endif