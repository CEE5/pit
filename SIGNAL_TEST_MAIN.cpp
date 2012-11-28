#include <iostream>
#include "signals.h"
#include "SignalListeErzeuger.h"

using namespace std;

int main()
{
    string longcat;
    cout << "File name:";
    cin >> longcat;
    SignalListeErzeuger* testlist = new SignalListeErzeuger(longcat);
    cout << "Read: " << testlist->getDatei() << endl;
    cout << "Vector size: " << testlist->getAnzahlSignale() << endl;
    cout << "Vectorcontent:"  << endl;
    for (int i=0;i<testlist->getAnzahlSignale();i++) {
        cout << "---------------------------------------------\n";
        cout << "Nummer: " << i << endl;
        cout << "Signaltyp: " << testlist->getSignal(i)->getSignalTyp() << endl;
        cout << "Quelle: " << testlist->getSignal(i)->getQuelle() << endl;
        cout << "Quellentyp: " << testlist->getSignal(i)->getQuellenTyp() << endl;
        cout << "Anzahlziele: " << testlist->getSignal(i)->getAnzahlZiele() << endl;
        for (int i1=0;i1<testlist->getSignal(i)->getAnzahlZiele();i1++) {
            cout << "-----" << testlist->getSignal(i)->getZiel(i1) <<endl;
        }
    }

    return 0;
}
