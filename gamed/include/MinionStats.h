#ifndef _MINION_STATS_H
#define _MINION_STATS_H

#include "Stats.h"


enum MinionFieldMaskOne : uint32
{
};

enum MinionFieldMaskTwo : uint32
{
   Minion_FM2_Ad      = 0x00001000,
   Minion_FM2_Atks    = 0x00004000
};

enum MinionFieldMaskThree : uint32
{
};

enum MinionFieldMaskFour : uint32
{
   Minion_FM4_MaxHp   =    0x00000001,
   Minion_FM4_CurrentHp =  0x00000002,
   Minion_FM4_MoveSpeed =  0x00000004
};

enum MinionFieldMaskFive : uint32
{
};

class MinionStats : public Stats {

public:
   float getMaxHealth() const {
      return getStat(MM_Four, Minion_FM4_MaxHp);
   }
   
   float getCurrentHealth() const {
      return getStat(MM_Four, Minion_FM4_CurrentHp);
   }
   
   float getBaseAd() const {
      return getStat(MM_Two, Minion_FM2_Ad);
   }
   
   float getAttackSpeed() const {
      return getStat(MM_Two, Minion_FM2_Atks);
   }
   
   float getMovementSpeed() const {
      return getStat(MM_Four, Minion_FM4_MoveSpeed);
   }
   

   void setMaxHealth(float health) {
      setStat(MM_Four, Minion_FM4_MaxHp, health);
      updatedHealth = true;
   }
   
   void setCurrentHealth(float health) {
      setStat(MM_Four, Minion_FM4_CurrentHp, health);
      updatedHealth = true;
   }
   
   void setBaseAd(float ad) {
      setStat(MM_Two, Minion_FM2_Ad, ad);
   }
   
   void setAttackSpeed(float speed) {
      setStat(MM_Two, Minion_FM2_Atks, speed);
   }
   
   void setMovementSpeed(float speed) {
      setStat(MM_Four, Minion_FM4_MoveSpeed, speed);
   }

};

#endif