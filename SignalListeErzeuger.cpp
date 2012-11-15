#include "SignalListeErzeuger.h"

SignalListeErzeuger::SignalListeErzeuger()
{
    //ctor
}

SignalListeErzeuger::~SignalListeErzeuger()
{
    //dtor
}

long SignalListeErzeuger::getFrequenz(){
    return frequenz;
}
string SignalListeErzeuger::getDatei() {
    return datei;
}
short SignalListeErzeuger::getAnzahlSignale(){
    return anzahlSignale;
}
void SignalListeErzeuger::setFrequenz(long freq){
    frequenz = freq;
}
void SignalListeErzeuger::setDatei(string file){
    datei = file;
}
void SignalListeErzeuger::setAnzahlSignale(short nSigs){
    anzahlSignale = nSigs;
}
