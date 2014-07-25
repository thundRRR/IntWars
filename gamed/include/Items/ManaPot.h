
#ifndef MANAPOT_H
#define	MANAPOT_H

class ManaPot : public Item{
    
    public:
    
    ManaPot() : Item(){
        id =2004;
        isStackable = true;
        active=true;
        price = 35;
    }
    
    
};



#endif	/* MANAPOT_H */

