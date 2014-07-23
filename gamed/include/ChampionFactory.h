#ifndef _CHAMPION_FACTORY_H
#define _CHAMPION_FACTORY_H

#include "Champions/Corki/Corki.h"
#include "Champions/Ezreal/Ezreal.h"
#include "Champions/Jinx/Jinx.h"
#include "Champions/Teemo/Teemo.h"
#include "Champions/Tryndamere/Tryndamere.h"
#include "Champions/Vayne/Vayne.h"

class ChampionFactory {

public:

   /**
    * Todo : Code every champion and add em here..
    */
   static Champion* getChampionFromType(const std::string& type, Map* map, uint32 id) {
      if(type == "Corki") {
         return new Corki(map, id);
      }
      if(type == "Ezreal") {
         return new Ezreal(map, id);
      }
      if(type == "Jinx") {
         return new Jinx(map, id);
      }
      if(type == "Teemo") {
         return new Teemo(map, id);
      }
      if(type == "Tryndamere") {
         return new Tryndamere(map, id);
      }
      if(type == "Vayne") {
         return new Vayne(map, id);
      }
      
      return new Champion(type, map, id);
   }


};

#endif