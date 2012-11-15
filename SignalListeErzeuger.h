#ifndef SIGNALLISTEERZEUGER_H
#define SIGNALLISTEERZEUGER_H

#include <iostream>
#include <string.h>

using namespace std;

class SignalListeErzeuger
{
    public:
        SignalListeErzeuger();
        virtual ~SignalListeErzeuger();
        long getFrequenz();
        string getDatei();
        short getAnzahlSignale();
        void setFrequenz(long freq);
        void setDatei(string file);
        void setAnzahlSignale(short nSigs);
    protected:
    private:
        long frequenz;
        string datei;
        short anzahlSignale;
};

#endif // SIGNALLISTEERZEUGER_H
