#ifndef _CHAMPION_JINX_H
#define _CHAMPION_JINX_H

#include "Champion.h"

class Jinx : public Champion {

public:
   Jinx(Map* map, uint32 id) : Champion("Jinx", map, id) {
      stats->setCurrentHealth(462.0f);
      stats->setMaxHealth(462.0f);
      stats->setCurrentMana(215.0f);
      stats->setMaxMana(215.0f);
      stats->setBaseAd(53.0f);
      stats->setRange(525.f);
      stats->setMovementSpeed(325.f);
      stats->setArmor(20.5f);
      stats->setMagicArmor(30.f);
      stats->setHp5(5.5f);
      stats->setMp5(6.0f);
   }


};

#endif