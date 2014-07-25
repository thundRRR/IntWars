
#ifndef HEALTHPOT_H
#define	HEALTHPOT_H

#include "../Item.h"



class HealthPot : public Item{
    
    public:
    
    HealthPot() : Item(){
        id =2003;
        isStackable = true;
        active=true;
        price = 35;
    }
    
    
};

#endif	/* HEALTHPOT_H */

