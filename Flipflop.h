#ifndef FLIPFLOP_H
#define FLIPFLOP_H
#include "GatterTyp.h"

class Flipflop : public GatterTyp
{
    public:
        Flipflop();
        virtual ~Flipflop();

        bool getIsFlipflop(void);
        short getSetupTime(void);
        short getHoldTime(void);
        short getLastKapazitaet(void);
        void setSetupTime(short st);
        void setHoldTime(short ht);
        void setLastKapazitaetClock(short lkc);

    protected:
    private:
        short setupTime;
        short  holdTime;
        short lastKapazitaetclock;

};

#endif // FLIPFLOP_H
