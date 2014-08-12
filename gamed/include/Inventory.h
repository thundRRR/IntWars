#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_STACK_AMOUNT 5

#include "Item.h"


class Inventory {
private:
   std::vector<ItemInstance*> items;

public:
    
   Inventory() {
      items = { 0, 0, 0, 0, 0, 0, 0 };
   }
   
   const ItemInstance* addItem(const ItemTemplate* itemTemplate);
   void swapItems(uint8 slotFrom, uint8 slotTo);
   const std::vector<ItemInstance*>& getItems() const { return items; }
    
};

#endif   /* INVENTORY_H */

