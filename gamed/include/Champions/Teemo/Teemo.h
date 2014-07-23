#ifndef _CHAMPION_TEEMO_H
#define _CHAMPION_TEEMO_H

#include "Champion.h"

class Teemo : public Champion {

public:
   Teemo(Map* map, uint32 id) : Champion("Teemo", map, id) {
      stats->setCurrentHealth(378.0f);
      stats->setMaxHealth(378.0f);
      stats->setCurrentMana(240.0f);
      stats->setMaxMana(240.0f);
      stats->setBaseAd(47.5f);
      stats->setRange(500.f);
      stats->setMovementSpeed(330.f);
      stats->setArmor(21.75f);
      stats->setMagicArmor(30.f);
      stats->setHp5(5.3f);
      stats->setMp5(7.9f);
   }


};

#endif