#ifndef __H_STATS
#define __H_STATS

#include <map>
#include <set>

#include "Buffer.h"

class Stats {

private:
   std::map<uint32, float> stats[5];
   std::set<std::pair<uint8, uint32> > updatedStats;
   
public:
   float getStat(uint8 blockId, uint32 stat);

};

#endif