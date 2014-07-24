
/* 
 * File:   Inventory.h
 * Author: Gusor
 *
 * Created on 24. heinäkuuta 2014, 11:35
 */

#ifndef INVENTORY_H
#define	INVENTORY_H

#define MAX_STACK_AMOUNT 5


#include "Item.h"

#include "Items/NoItem.h"


class Inventory{
           
public:
    
	Inventory();


	Item items[6];//0-5 = default items, 6 = trinket
        
        void setItem(Item &item, Item newItem){
            item = newItem;
        }
        

    
    bool addItemNew(Item _item);
    
    bool containsItem(int id);
    

    
};

#endif	/* INVENTORY_H */

