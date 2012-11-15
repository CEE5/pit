#ifndef GATTERTYP_H
#define GATTERTYP_H

#include <string>

using namespace std;

class GatterTyp
{
    public:
        GatterTyp();
        virtual ~GatterTyp();

        string getName(void);
        double getGrundLaufzeit(void);
        short getLastFaktor(void);
        short getLastKapazitaet(void);
        short getEingaenge(void);
        bool getIsFlipFlop(void);
        void setName(string n);
        void setGrundLaufzeit(double gl);
        void setLastFaktor(short lf);
        void setLastKapazitaet(short lk);
        void seteingaenge(short ei);


    protected:
        string name;
        double grundLaufzeit;
        short lastFaktor;
        short lastKapazitaet;
        short eingaenge;

    private:
};

#endif // GATTERTYP_H
