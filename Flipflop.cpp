#include "Flipflop.h"
#include <iostream>

Flipflop::Flipflop()
{
    //ctor

}

Flipflop::~Flipflop()
{
    //dtor
}
        bool Flipflop::getIsFlipflop(void){
            return true;
        }
        short Flipflop::getSetupTime(void){
            return setupTime;
        }
        short Flipflop::getHoldTime(void){
            return holdTime;
        }
        void Flipflop::setSetupTime(short st){
            setupTime=st;
        }
        void Flipflop::setHoldTime(short ht){
            holdTime = ht;
        }
        void Flipflop::setLastKapazitaetClock(short lkc){
            lastKapazitaetClock = lkc;
        }
        short Flipflop::getLastKapazitaetClock(){
            return lastKapazitaetClock;
        }

