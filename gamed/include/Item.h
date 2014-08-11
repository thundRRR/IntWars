#ifndef ITEM_H
#define ITEM_H

#include "stdafx.h"
#include <vector>

class ItemTemplate
{
private:
   uint32 id;
   uint32 maxStack;
   uint32 price;
   float sellBackModifier;
   
   /**
    * Necessary items to create this one.
    */
   std::vector<ItemTemplate*> recipes;
   
public:
   ItemTemplate(uint32 id, uint32 maxStack, uint32 price, float sellBackModifier) : id(id), maxStack(maxStack), price(price), sellBackModifier(sellBackModifier) { }
   
   uint32 getId() const { return id; }
   uint32 getMaxStack() const { return maxStack; }
   uint32 getPrice() const { return price; }
   float getSellBackModifier() const { return sellBackModifier; }
   
   bool isRecipe() const { return recipes.size() > 0; }

};

class ItemInstance {
private:
   const ItemTemplate* itemTemplate;
   float cooldown;

public:
   ItemInstance(const ItemTemplate* itemTemplate) : itemTemplate(itemTemplate), cooldown(0) { }
   const ItemTemplate* getTemplate() { return itemTemplate; }

};

#endif   /* ITEM_H */

