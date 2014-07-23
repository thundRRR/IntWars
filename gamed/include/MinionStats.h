#ifndef _MINION_STATS_H
#define _MINION_STATS_H

#include "Stats.h"


enum MinionFieldMaskOne : uint32
{
};

enum MinionFieldMaskTwo : uint32
{
};

enum MinionFieldMaskThree : uint32
{
};

enum MinionFieldMaskFour : uint32
{
   Minion_FM4_CurrentHp   = 0x00000001,
   Minion_FM4_MaxHp =       0x00000002,
};

enum MinionFieldMaskFive : uint32
{
};

class MinionStats : public Stats {

public:
   float getMaxHealth() const {
      return getStat(MM_Four, Minion_FM4_MaxHp);
   }

   void setMaxHealth(float health) {
      setStat(MM_Four, Minion_FM4_MaxHp, health);
   }

};

#endif