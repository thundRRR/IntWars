#ifndef _UNIT_H
#define _UNIT_H

#include "Object.h"
#include "Stats.h"

class Unit : public Object {

protected:
   Stats stats;
   virtual void update(unsigned int diff) { }

public:
   Unit(Map* map, uint32 id) : Object(map, id, 0, 0, 0, 0) { }
   virtual ~Unit() { }

};

#endif