#ifndef _CHAMPION_EZREAL_H
#define _CHAMPION_EZREAL_H

#include "Champion.h"
#include "MysticShot.h"

class Ezreal : public Champion {

public:
   Ezreal(Map* map, uint32 id) : Champion("Ezreal", map, id) {
      spells.push_back(new MysticShot(this));
      spells.push_back(new MysticShot(this));
      spells.push_back(new MysticShot(this));
      spells.push_back(new MysticShot(this));
      
      stats->setCurrentHealth(430.0f);
      stats->setMaxHealth(430.0f);
      stats->setCurrentMana(280.0f);
      stats->setMaxMana(280.0f);
      stats->setBaseAd(50.2f);
      stats->setRange(550.f);
      stats->setMovementSpeed(325.f);
      stats->setArmor(19.5f);
      stats->setMagicArmor(30.f);
   }


};

#endif