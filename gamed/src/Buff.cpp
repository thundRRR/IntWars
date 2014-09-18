#include "Unit.h"
#include "Game.h"
#include "Buff.h"
#include "LuaScript.h"


void Buff::update(int64 diff){
   timeElapsed += (float)diff/1000000.0f;
   
   
      if(buffScript != 0 && buffScript->isLoaded()){
      buffScript->lua.get <sol::function> ("onUpdate").call <void> (diff);
   }else{
   }
      if(getBuffType() != BUFFTYPE_ETERNAL){
         if(timeElapsed >= duration){
            if(name != ""){ // empty name = no buff icon
            attachedTo->getMap()->getGame()->notifyRemoveBuff(attachedTo, name);
         }
      remove = true;
      }
   }
}

Buff::Buff(std::string buffName, float dur, BuffType type, Unit* u, Unit* uu)  : duration(dur),  name(buffName), timeElapsed(0), remove(false), attachedTo(u) , attacker(uu), buffType(type), movementSpeedPercentModifier(0.0f)  {
   //init();
   if(name != ""){ // empty name = no buff icon
   std::string scriptloc = "../../lua/buffs/" + name + ".lua";
	printf("Loading %s\n", scriptloc.c_str());
   try{
   
    buffScript = new LuaScript(true);//fix
    
    buffScript->loadScript(scriptloc);
    buffScript->setLoaded(true);
    
    printf("Loaded buff lua script\n");
    buffScript->lua.set_function("getAttachedUnit", [this]() { 
      return attachedTo;
   });
   
   buffScript->lua.set_function("dealMagicDamage", [this](Unit* target, float amount) { attacker->dealDamageTo(target,amount,DAMAGE_TYPE_MAGICAL,DAMAGE_SOURCE_SPELL); });

    printf("added lua buff script functions\n");
   }catch(sol::error e){//lua error? don't crash the whole server
      buffScript->setLoaded(false);
      printf("Lua buff load error: \n%s\n", e.what());
   }
   
   
      attachedTo->getMap()->getGame()->notifyAddBuff(attachedTo, name);
   }
}


