#ifndef _SPELL_H
#define _SPELL_H

class Champion;

class Spell {
protected:
   uint32 id;
   Champion* owner;
   uint8 level;
   
   float castTime;
   float cooldown[5];
   float cost[5];

   
   Object* target;
   float x, y;
   
public:
   Spell(uint32 id, Champion* owner, float castTime) : id(id), owner(owner), level(0), castTime(castTime) { }
   virtual bool cast(float x, float y, Object* o = 0) = 0;
   
   Champion* getOwner() const { return owner; }
   uint32 getId() const { return id; }
   float getCastTime() const { return castTime; }
   
   /**
    * TODO : Add in CDR % from champion's stat
    */
   float getCooldown() const { 
      if(!level) {
         return 0;
      }
      return cooldown[level-1];
   }
   
   float getCost() const {
      if(!level) {
         return 0;
      }
      return cost[level-1];
   }

};

#endif