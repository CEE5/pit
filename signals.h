/** Signal Class Header File
created by Benibr**/

#ifndef SIGNAL_HEADER
#define SIGNAL_HEADER

#include <string>
#include <iostream>
#include <vector>

enum signalTypen {eingang, intern, ausgang, unbekannt, clk};

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
        void zielHinzufuegen(string gatterno);
    protected:
    private:
        string quelle;
        string quellenTyp;
        vector <string> ziele;
        int anzahlZiele;
        signalTypen signalTyp;
};


#endif
