#include "Unit.h"

class Champion : public Unit {

protected:
   std::string type;
   
public:
   Champion(const std::string& type, Map* map, uint32 id) : Unit::Unit(map, id), type(type) { }
   const std::string& getType() { return type; }


};