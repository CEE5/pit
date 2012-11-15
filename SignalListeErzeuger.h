#ifndef SIGNALLISTEERZEUGER_H
#define SIGNALLISTEERZEUGER_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>

using namespace std;

/** SignalListeErzeuger
Liest die komplette Datei ein, sortiert und erzeugt Liste.
Kritik von Lukas: sollte laut Name nur Liste erstellen.
**/

class SignalListeErzeuger
{
    public:
        SignalListeErzeuger(string file);
        virtual ~SignalListeErzeuger();
        int readFile();
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
