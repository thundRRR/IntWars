#ifndef _CHAMPION_VAYNE_H
#define _CHAMPION_VAYNE_H

#include "Champion.h"

class Vayne : public Champion {

public:
   Vayne(Map* map, uint32 id) : Champion("Vayne", map, id) {
      stats->setCurrentHealth(442.0f);
      stats->setMaxHealth(442.0f);
      stats->setCurrentMana(208.0f);
      stats->setMaxMana(208.0f);
      stats->setBaseAd(53.25f);
      stats->setRange(550.f);
      stats->setMovementSpeed(330.f);
      stats->setArmor(13.3f);
      stats->setMagicArmor(30.f);
      stats->setHp5(5.05f);
      stats->setMp5(6.7f);
   }


};

#endif