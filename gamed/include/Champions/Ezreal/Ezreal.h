#ifndef _CHAMPION_EZREAL_H
#define _CHAMPION_EZREAL_H

#include "Champion.h"
#include "MysticShot.h"
#include "ArcaneShift.h"

class Ezreal : public Champion {

public:
   Ezreal(Map* map, uint32 id) : Champion("Ezreal", map, id) {
      spells.push_back(new MysticShot(this));
      spells.push_back(new MysticShot(this));
      spells.push_back(new ArcaneShift(this));
      spells.push_back(new MysticShot(this));
   }


};

#endif