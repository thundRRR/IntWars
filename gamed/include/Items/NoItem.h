

#ifndef NOITEM_H
#define	NOITEM_H

class NoItem : public Item{
    
    public:
    
    NoItem() : Item(){
        id = -1;
        active = false;
    }
    
    
};


#endif	/* NOITEM_H */

