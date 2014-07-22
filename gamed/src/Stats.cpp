#include "Stats.h"
#include "common.h"

float Stats::getStat(uint8 blockId, uint32 stat) const {
   int block = -1;
   while(blockId) {
      blockId = blockId >> 1;
      ++block;
   }
   auto it = stats[block].find(stat);
   if(it != stats[block].end()) {
      return it->second;
   }
   
   return 0;
}

float Stats::setStat(uint8 blockId, uint32 stat, float value) {
   int block = -1;
   while(blockId) {
      blockId = blockId >> 1;
      ++block;
   }
   stats[block][stat] = value;
}

float Stats::getCurrentHealth() const {
   return getStat(MM_Four, FM4_CurrentHp);
}

float Stats::getMaxHealth() const {
   return getStat(MM_Four, FM4_MaxHp);
}

void Stats::setCurrentHealth(float health) {
   setStat(MM_Four, FM4_CurrentHp, health);
}

void Stats::setMaxHealth(float health) {
   setStat(MM_Four, FM4_MaxHp, health);
}