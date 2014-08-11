#include "ItemManager.h"
#include "RAFManager.h"
#include "Inibin.h"

#include <string>

using namespace std;

ItemManager* ItemManager::instance = 0;

void ItemManager::init() {
   // TODO : this is highly inefficient
   std::vector<unsigned char> iniFile;
   
   for(uint32 i = 1000; i < 4000; ++i) {
      iniFile.clear();
      if(!RAFManager::getInstance()->readFile("DATA/items/"+to_string(i)+".inibin", iniFile)) {
         continue;
      }
   
      Inibin inibin(iniFile);
      
      uint32 maxStack = inibin.getIntValue("DATA", "MaxStack");
      uint32 price = inibin.getIntValue("DATA", "Price");
      
      float sellBack = 0.7f;
      
      if(inibin.keyExists("DATA", "SellBackModifier")) {
         sellBack = inibin.getFloatValue("DATA", "SellBackModifier");
      }
      
      itemTemplates[i] = new ItemTemplate(i, maxStack, price, sellBack);
   
   }
   
   printf("Loaded %lu items\n", itemTemplates.size());
}

const ItemTemplate* ItemManager::getItemTemplateById(uint32 id) {
   if(itemTemplates.find(id) == itemTemplates.end()) {
      return 0;
   }
   
   return itemTemplates[id];
}