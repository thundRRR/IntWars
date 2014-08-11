#include "Inventory.h"
#include "stdafx.h"

using namespace std;

bool Inventory::addItem(const ItemTemplate* itemTemplate) {
   int slot = -1;

   if(itemTemplate->getMaxStack() > 1) {
      for(slot = 0; slot < 7; ++slot) {
         if(slot == 3 || items[slot].first == 0) { // trinket slot
            continue;
         }
      
         if(items[slot].first->getTemplate() == itemTemplate && items[slot].second < itemTemplate->getMaxStack()) {
            ++items[slot].second;
            return true;
         }
      }
   }
   
   if(slot == -1 || slot == 7) {
      for(slot = 0; slot < 7; ++slot) {
         if(slot == 3) { // trinket slot
            continue;
         }
      
         if(items[slot].first == 0) {
            break;
         }
      }
   }
   
   if(slot == 7) { // Inventory full
      return false;
   }
   
   items[slot] = make_pair(new ItemInstance(itemTemplate), 1);
   
   return true;
}