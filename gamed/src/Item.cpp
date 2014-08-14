#include "Item.h"
#include "ItemManager.h"

uint32 ItemTemplate::getTotalPrice() const {
   uint32 toReturn = price;
   
   for(uint32 itemId : recipes) {
      toReturn += ItemManager::getInstance()->getItemTemplateById(itemId)->getTotalPrice();
   }
   
   return toReturn;
}