/** Signal Class Header File
created by Benibr**/

#ifndef SIGNAL_HEADER
#define SIGNAL_HEADER

#include <string>
#include <iostream>

enum signalTypen {eingang, intern, ausgang, unbekannt};

using namespace std;

class Signal
{
    public:
        Signal();
        ~Signal();
        signalTypen getSignalTyp();
        int getAnzahlZiele();
        string getQuelle();
        string getQuellenTyp();
        string getZiel(int pos);
        signalTypen setSignalTyp(signalTypen sigTyp);
        void setQuelle(string gatterName);
        void setQuellentyp(string gatterTyp);
        void setAnzahlZiele(int nZiele);
        void zielHinzufuegen(string gattername, int pos);
    protected:
    private:
        string quelle;
        string quellenTyp;
        string ziele;
        int anzahlZiele;
        signalTypen signalTyp;
};


#endif
