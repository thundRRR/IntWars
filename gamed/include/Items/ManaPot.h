/* 
 * File:   ManaPot.h
 * Author: Gusor
 *
 * Created on 24. heinäkuuta 2014, 19:02
 */

#ifndef MANAPOT_H
#define	MANAPOT_H

class ManaPot : public Item{
    
    public:
    
    ManaPot() : Item(){
        id =2004;
        isStackable = true;
        active=true;
    }
    
    
};



#endif	/* MANAPOT_H */

