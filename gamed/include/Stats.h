#ifndef __H_STATS
#define __H_STATS

#include <map>

#include "stdafx.h"
#include "common.h"

class Stats {

private:
   std::map<uint32, float> stats[5];
   std::multimap<uint8, uint32> updatedStats;
   
public:
   float getStat(uint8 blockId, uint32 stat) const;
   void setStat(uint8 blockId, uint32 stat, float value);

   const std::multimap<uint8, uint32>& getUpdatedStats() const { return updatedStats; }
   void clearUpdatedStats() { updatedStats.clear(); }

   float getBaseAd() const {
      return getStat(MM_Two, FM2_Base_Ad);
   }
   
   float getBaseAp() const {
      return getStat(MM_Two, FM2_Base_Ap);
   }
   
   float getCritChance() const {
      return getStat(MM_Two, FM2_Crit_Chance);
   }
   
   float getArmor() const {
      return getStat(MM_Two, FM2_Armor);
   }
   
   float getMagicArmor() const {
      return getStat(MM_Two, FM2_Magic_Armor);
   }
   
   float getRange() const {
      return getStat(MM_Two, FM2_Range);
   }
   
   float getCurrentHealth() const {
      return getStat(MM_Four, FM4_CurrentHp);
   }

   float getMaxHealth() const {
      return getStat(MM_Four, FM4_MaxHp);
   }
   
   float getMovementSpeed() const {
      return getStat(MM_Four, FM4_Speed);
   }


   void setBaseAd(float ad) {
      setStat(MM_Two, FM2_Base_Ad, ad);
   }
   
   void setRange(float range) {
      setStat(MM_Two, FM2_Range, range);
   }
   
   void setArmor(float armor) {
      setStat(MM_Two, FM2_Armor, armor);
   }
   
   void setMagicArmor(float armor) {
      setStat(MM_Two, FM2_Magic_Armor, armor);
   }
   
   void setCurrentHealth(float health) {
      setStat(MM_Four, FM4_CurrentHp, health);
   }

   void setMaxHealth(float health) {
      setStat(MM_Four, FM4_MaxHp, health);
   }
   
   void setMovementSpeed(float speed) {
      setStat(MM_Four, FM4_Speed, speed);
   }
   
   void setGold(float gold) {
      setStat(MM_One, FM1_Gold, gold);
   }

};

#endif