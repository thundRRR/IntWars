#include "Spell.h"
#include "RAFManager.h"
#include "Champion.h"
#include "Inibin.h"

using namespace std;

Spell::Spell(Champion* owner, const std::string& spellName, uint8 slot) : owner(owner), spellName(spellName), level(0), slot(slot), state(STATE_READY), currentCooldown(0), currentCastTime(0) {
   std::vector<unsigned char> iniFile;
   if(!RAFManager::getInstance()->readFile("DATA/Spells/"+spellName+".inibin", iniFile)) {
      if(!RAFManager::getInstance()->readFile("DATA/Characters/"+owner->getType()+"/"+spellName+".inibin", iniFile)) {
         printf("ERR : couldn't find spell stats for %s\n", spellName.c_str());
         return;
      }
   }
   
   Inibin inibin(iniFile);
   
   for(int i = 0; i < 5; ++i) {
      char c = '0'+i+1;
      cooldown[i] = inibin.getFloatValue("SpellData", string("Cooldown")+c);
   }
   
   castTime = (1+inibin.getFloatValue("SpellData", "DelayCastOffsetPercent")) * 500;
}

/**
 * Called when the character casts the spell
 */
bool Spell::cast(float x, float y, Unit* u) {
   state = STATE_CASTING;
   currentCastTime = castTime;
   
   this->x = x;
   this->y = y;
   this->target = u;
   
   return true;
}

/**
 * Called when the spell is finished casting and we're supposed to do things
 * such as projectile spawning, etc.
 */
void Spell::finishCasting() {
   state = STATE_COOLDOWN;
   currentCooldown = getCooldown();
}

/**
 * Called every diff milliseconds to update the spell
 */
void Spell::update(int64 diff) {
   switch(state) {
      case STATE_READY:
         return;
      case STATE_CASTING:
         currentCastTime -= diff/1000000.f;
         if(currentCastTime < 0) {
            finishCasting();
         }
         break;
      case STATE_COOLDOWN:
         currentCooldown -= diff/1000000.f;
         if(currentCooldown < 0) {
            state = STATE_READY;
         }
         break;
   }
}

uint32 Spell::getId() const {
   return RAFFile::getHash(owner->getType()+spellName);
}

void Spell::applyEffects(Target* t, Projectile* p) {
   
}