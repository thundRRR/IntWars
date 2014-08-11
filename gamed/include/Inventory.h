#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_STACK_AMOUNT 5

#include "Item.h"


class Inventory {
private:
   std::vector<std::pair<ItemInstance*, uint8> > items;

public:
    
   Inventory() {
      items = { std::make_pair<ItemInstance*, uint8>(0, 0), std::make_pair<ItemInstance*, uint8>(0, 0), std::make_pair<ItemInstance*, uint8>(0, 0), std::make_pair<ItemInstance*, uint8>(0, 0), std::make_pair<ItemInstance*, uint8>(0, 0), std::make_pair<ItemInstance*, uint8>(0, 0), std::make_pair<ItemInstance*, uint8>(0, 0) };
   }
   
   bool addItem(const ItemTemplate* itemTemplate);
   const std::vector<std::pair<ItemInstance*, uint8> >& getItems() const { return items; }
    
};

#endif   /* INVENTORY_H */

