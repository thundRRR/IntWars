/* 
 * File:   Inventory.cpp
 * Author: Skar
 * 
 * Created on 24. heinäkuuta 2014, 11:54
 */

#include "Inventory.h"
#include "stdafx.h"

Inventory::Inventory() {
    

}

bool Inventory::containsItem(int id){
   for (int i = 0; i < 5; i++){
        if (items[i].active == true && items[i].id == id){
            return true;
        }
   }
    return false;
}

bool Inventory::addItemNew(Item _item ) {
                printf("inventory::addItemNew :%i\n", _item.id);
    for (int i = 0; i < 5; i++){

		if (items[i].id == _item.id){
			
			if (items[i].isStackable == true){
                     printf("stack++ %i", i);
				if (items[i].stackAmount < MAX_STACK_AMOUNT){
					items[i].stackAmount++;
					items[i].active = true;
					return true;
				}



			}
		}
		if (items[i].active == false){
			items[i] = _item;
			items[i].stackAmount = 1;
			items[i].active = true;
         printf("item is active, added %i\n", i);
         
         printf("Id is now: %i\n", items[i].id);
         
			return true;
		}
    }
    return false;
}