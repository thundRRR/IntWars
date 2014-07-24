#ifndef _CHAMPION_TRYNDAMERE_H
#define _CHAMPION_TRYNDAMERE_H

#include "Champion.h"

class Tryndamere : public Champion {

public:
   Tryndamere(Map* map, uint32 id) : Champion("Tryndamere", map, id) {
      stats->setCurrentHealth(657.0f);
      stats->setMaxHealth(657.0f);
      stats->setCurrentMana(100.0f); //TODO: Distinguish mana and Energy?
      stats->setMaxMana(100.0f);
      stats->setBaseAd(62.2f);
      stats->setRange(125.f);
      stats->setMovementSpeed(345.f);
      stats->setArmor(25.1f);
      stats->setMagicArmor(32.55f);
      stats->setHp5(8.8f);
      stats->setMp5(0.0f);          //TODO: Distinguish mana and Energy?
   }


};

#endif