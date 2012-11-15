#include "Bibliothek.h"
#include <iostream>

Bibliothek::Bibliothek()
{
    //ctor
}

Bibliothek::~Bibliothek()
{
    //dtor
}

//Dient zum Lesen des Pfads und Dateinamen, welche im Attribut datei gespeichert sind
string Bibliothek::getPfad(void)
{
    return datei;
}
/**Dieser Methode wird ein string, des Gattertyps (z.B. inv1a), übergegeben.
Sie gibt einen Zeiger auf das entsprechende Element vom Typ GatterTyp zurück.
*/
/*GatterTyp Bibliothek::getBibElement(string)
{

}*/

/**Ausgabe der Datei auf dem Bildschirm, dabei sollen die Zeilen durchnummeriert werden.
Dabei  soll,  falls  die  Datei  nicht  vorhanden  ist  oder  ein  Fehler  beim  Lesen  auftritt,
das Programm nicht abstürzen, sondern eine Fehlermeldung ausgeben. */
void Bibliothek::dateiAusgabe(void)
{

}
/**Die  Methode  dient  zum  Einlesen  und  Auswerten  der  Bibliotheksdatei.
Dabei soll  jeder  in  der  Datei  beschriebene  Gattertyp  in  einem  Element  vom  Typ
GatterTyp  im  Vektor bibElemente  gespeichert  werden.  Die  Reihenfolge  ist
dabei  nicht  wichtig.  Das  Flipﬂop  kann  dabei am  Namen  erkannt  werden,  welcher  als  bekannt  vorausgesetzt  wird.
Das  Flipﬂop  wird  in  einem Element vom Typ Flipflop im Vektor bibElemente gespeichert. */
void Bibliothek::dateiAuswerten(void)
{
    ifstream f(datei.c_str());

    string buffer;
    while (!f.eof())
    {
        getline(f,buffer);
//        if()
        cout << buffer << endl;
    }

}
/**Speichert den Pfad zu Bibliotheksdatei im entsprechenden Attribut,
falls diese unter dem angegebenen Pfad vorhanden ist und sie geöﬀnet werden kann.
*/
bool Bibliothek::pfadEinlesen(string pfad)
{

    ifstream f(pfad.c_str());
    if(f.is_open()){
        datei = pfad;

    }
    else{
        openError();
    }


}

/**Ausgabe einer Fehlermeldung beim Öﬀnen einer Datei. */
void Bibliothek::openError(void)
{
    cerr <<"open error"<<endl;

}
/**Ausgabe einer Fehlermeldung beim Lesen einer Datei.
*/
void Bibliothek::readError(void)
{

}
