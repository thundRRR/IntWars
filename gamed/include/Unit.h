#ifndef _UNIT_H
#define _UNIT_H

#include "Object.h"

class Unit : public Object {

protected:
   virtual void update(unsigned int diff) { }

public:
   Unit(Map* map, uint32 id) : Object(map, id, 0, 0, 0, 0) { }
   virtual ~Unit() { }

};

#endif