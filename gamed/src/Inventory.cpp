#include "Inventory.h"
#include "stdafx.h"

using namespace std;

const ItemInstance* Inventory::addItem(const ItemTemplate* itemTemplate) {
   int slot = -1;
   
   if(itemTemplate->isTrinket()) {
      if(items[6] == 0) {
         items[6] = new ItemInstance(itemTemplate, 6, 1);
         return items[6];
      }
      
      return 0;
   }

   if(itemTemplate->getMaxStack() > 1) {
      for(slot = 0; slot < 7; ++slot) {
         if(slot == 6 || items[slot] == 0) { // trinket slot
            continue;
         }
      
         if(items[slot]->getTemplate() == itemTemplate && items[slot]->getStacks() < itemTemplate->getMaxStack()) {
            items[slot]->incrementStacks();
            return items[slot];
         }
      }
   }
   
   if(slot == -1 || slot == 7) {
      for(slot = 0; slot < 7; ++slot) {
         if(slot == 6) { // trinket slot
            continue;
         }
      
         if(items[slot] == 0) {
            break;
         }
      }
   }
   
   if(slot == 7) { // Inventory full
      return 0;
   }
   
   printf("Adding item %d to slot %d\n", itemTemplate->getId(), slot);
   items[slot] = new ItemInstance(itemTemplate, slot, 1);
   
   return items[slot];
}

void Inventory::swapItems(uint8 slotFrom, uint8 slotTo) {
   ItemInstance* to = items[slotTo];
   items[slotTo] = items[slotFrom];
   items[slotFrom] = to;
}