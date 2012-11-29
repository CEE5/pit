#ifndef SIGNALLISTEERZEUGER_H
#define SIGNALLISTEERZEUGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "signals.h"

using namespace std;

/** SignalListeErzeuger
Liest die komplette Datei ein, sortiert und erzeugt Liste.
Kritik von Lukas: sollte laut Name nur Liste erstellen.
**/

class SignalListeErzeuger
{
    public:
<<<<<<< HEAD
        SignalListeErzeuger();           ///CTor führt readFile aus
=======
        SignalListeErzeuger();           ///CTor
>>>>>>> 9a6ad6ee806721bdfecf073150abeed0ef6528d0
        virtual ~SignalListeErzeuger();             ///DTor
        Signal* getSignal(int i);                   ///gibt Instanz an der Stelle i im vector signale zurück
        int readFile();                             ///Liest Datei ein und für sortierfunktion aus
        int readSignalLine(signalTypen typ, int lengthBegin, string line);                            ///Liest nach Signaltyp vorsortierte Zeile ein
        int readGateLine(string tmpLine);
        long getFrequenz();
        string getDatei();
        short getAnzahlSignale();
        void setFrequenz(long freq);
        void setDatei(string file);                 ///Liest Datei NICHT ein
        void setAnzahlSignale(short nSignals);
    protected:
    private:
        vector <Signal> signale;                    ///Vector mit Signal Instanzen
        long frequenz;
        string datei;                               ///Pfad zur Schaltnetz Datei
        short anzahlSignale;
};

#endif // SIGNALLISTEERZEUGER_H
