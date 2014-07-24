
#ifndef HEALTHPOT_H
#define	HEALTHPOT_H

#include "../Item.h"



class HealthPot : public Item{
    
    public:
    
    HealthPot() : Item(){
        id =2003;
        isStackable = true;
        active=true;
    }
    
    
};

#endif	/* HEALTHPOT_H */

