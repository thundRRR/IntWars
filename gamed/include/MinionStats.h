#ifndef _MINION_STATS_H
#define _MINION_STATS_H

#include "Stats.h"


enum MinionFieldMaskOne : uint32
{
};

enum MinionFieldMaskTwo : uint32
{
   Minion_FM2_CurrentHp =  0x00000001,
   Minion_FM2_Ad         = 0x00001000,
   Minion_FM2_Atks       = 0x00004000
};

enum MinionFieldMaskThree : uint32
{
};

enum MinionFieldMaskFour : uint32
{
   Minion_FM4_MaxHp   =    0x00000002,
   Minion_FM4_MoveSpeed =  0x00000004
};

enum MinionFieldMaskFive : uint32
{
};

class MinionStats : public Stats {

public:
   float getMaxHealth() const override {
      return getStat(MM_Four, Minion_FM4_MaxHp);
   }
   
   float getCurrentHealth() const override {
      return getStat(MM_Four, Minion_FM2_CurrentHp);
   }
   
   float getBaseAd() const override {
      return getStat(MM_Two, Minion_FM2_Ad);
   }
   
   float getAttackSpeed() const override {
      return getStat(MM_Two, Minion_FM2_Atks);
   }
   
   float getMovementSpeed() const override {
      return getStat(MM_Four, Minion_FM4_MoveSpeed);
   }
   

   void setMaxHealth(float health) override {
      setStat(MM_Four, Minion_FM4_MaxHp, health);
      updatedHealth = true;
   }
   
   void setCurrentHealth(float health) override {
      setStat(MM_Four, Minion_FM2_CurrentHp, health);
      updatedHealth = true;
   }
   
   void setBaseAd(float ad) override {
      setStat(MM_Two, Minion_FM2_Ad, ad);
   }
   
   void setAttackSpeed(float speed) override {
      setStat(MM_Two, Minion_FM2_Atks, speed);
   }
   
   void setMovementSpeed(float speed) override {
      setStat(MM_Four, Minion_FM4_MoveSpeed, speed);
   }

};

#endif