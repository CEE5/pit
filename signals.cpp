/** Signal Class CPP File
created by Benibr  **/

#include "signals.h"

/**Signal() Ist der Konstruktor der Klasse. Er soll beim Anlegen der Klasse alle Attribute mit dem Wert 0
bzw. „NULL“ für Strings und signalTyp als unbekannt initialisieren.**/
Signal::Signal () {
        quelle = "";
        quellenTyp = "";
        ziele = "";
        anzahlZiele = 0;
        signalTyp = unbekannt;
}
/**∼Signal() Ist der Destruktor der Klasse. Er soll implementiert werden, hat allerdings keine Aufgabe.**/
Signal::~Signal () {
    //dtor
}
/**type getName(void)
Diese Methoden dienen zum Lesen der privaten Attribute eines einzelnen Objekts vom Typ Signal.
Diese Methoden können auch inline implementiert werden.**/
int Signal::getAnzahlZiele() {
    return anzahlZiele;
};
signalTypen Signal::getSignalTyp() {
    return signalTyp;
}
string Signal::getQuelle() {
    return quelle;
};
string Signal::getQuellenTyp() {
    return quellenTyp;
};
string Signal::getZiel(int pos) {
    return ziele;
};

signalTypen Signal::setSignalTyp(signalTypen sigTyp) {
    signalTyp = sigTyp;
};

void Signal::setQuelle(string gatterName) {
    quelle = gatterName;
};

void Signal::setQuellentyp(string gatterTyp) {
    quellenTyp = gatterTyp;
};

void Signal::setAnzahlZiele(int nZiele) {
    anzahlZiele = nZiele;
};

void Signal::zielHinzufuegen(string gattername, int pos) {

};
