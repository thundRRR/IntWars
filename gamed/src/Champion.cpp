#include "Champion.h"

Champion::Champion(const std::string& type, Map* map, uint32 id) : Unit::Unit(map, id), type(type) {
   stats.setCurrentHealth(666.0f);
   stats.setMaxHealth(1337.0f);
}