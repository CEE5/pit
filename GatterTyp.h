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

    protected:
        string name;
        double grundLaufzeit;
        short lastFaktor;
        short lastKapazitaet;
        short eingaenge;

    private:
};

#endif // GATTERTYP_H
