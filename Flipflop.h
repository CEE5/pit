#ifndef FLIPFLOP_H
#define FLIPFLOP_H

using namespace std;

class Flipflop
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
        void setLastkapazitaetClock(short lkc);

    protected:
    private:
        short setupTime;
        short holdTime;
        short lastKapazitaetClock;
};

#endif // FLIPFLOP_H
