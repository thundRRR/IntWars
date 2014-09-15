#include "Unit.h"
#include "Game.h"
#include "Buff.h"


void Buff::update(int64 diff){
   printf("Update\n");
  // printf("Name is %s\n", name.c_str());//this line crashes, even though name is defined and print works from constructor.. wtf
   timeElapsed += (float)diff/1000000.0;
   if(timeElapsed >= duration){
attachedTo->getMap()->getGame()->notifyRemoveBuff(attachedTo, name);
    remove = true;

   }
}

Buff::Buff(std::string buffName, float dur, Unit* u)  /*: duration(dur),  name(buffName), timeElapsed(0), remove(false), attachedTo(u)*/{
duration = dur;
name = buffName;
timeElapsed = 0;
remove = false;
attachedTo = u;
printf("New buff!\n");
   printf("Beginning Buff name %s \n", getName().c_str());
   if(name != ""){ // empty name = no buff icon
   attachedTo->getMap()->getGame()->notifyAddBuff(attachedTo, name);
   }
   
   printf("Name is %s", name.c_str());

}

