

#ifndef BUFF_H
#define	BUFF_H

class Buff{
private:
float duration;
float movementSpeedPercentModifier;
float timeElapsed = 0;
bool remove = false;
    
public:
    
    bool needsToRemove(){  return remove;}
    Buff(float dur) : duration(dur){}
    
    float getMovementSpeedPercentModifier() { return movementSpeedPercentModifier;}
    
    void setMovementSpeedPercentModifier(float modifier){movementSpeedPercentModifier = modifier;}
    
    void update(uint64 diff){
        timeElapsed += (float)diff/1000000.0;
        if(timeElapsed >= duration){
            remove = true;
        }
    }
    
    
};


#endif	/* BUFF_H */

