#ifndef _CHAMPION_JINX_H
#define _CHAMPION_JINX_H

#include "Champion.h"

class Corki : public Champion {

public:
   Corki(Map* map, uint32 id) : Champion("Corki", map, id) {
      stats->setCurrentHealth(457.0f);
      stats->setMaxHealth(457.0f);
      stats->setCurrentMana(280.0f);
      stats->setMaxMana(280.0f);
      stats->setBaseAd(51.2f);
      stats->setRange(550.f);
      stats->setMovementSpeed(325.f);
      stats->setArmor(21.0f);
      stats->setMagicArmor(30.f);
      stats->setHp5(5.05f);
      stats->setMp5(7.05f);
   }


};

#endif