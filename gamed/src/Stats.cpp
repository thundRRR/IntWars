#include "Stats.h"
#include "common.h"

float Stats::getStat(uint8 blockId, uint32 stat) const {
   auto it = stats[blockId].find(stat);
   if(it != stats[blockId].end()) {
      return it->second;
   }
   
   return 0;
}

float Stats::setStat(uint8 blockId, uint32 stat, float value) {
   stats[blockId][stat] = value;
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