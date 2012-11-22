#include "Bibliothek.h"

Bibliothek::Bibliothek()
{
    vector<GatterTyp*> bibElemente;
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
GatterTyp Bibliothek::getBibElement(string)
{

}

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
        //"\r" entfernen
        buffer.erase(buffer.size()-1);

        //von [[Bausteine]] bis Leerzeile einlesen
        if(buffer.find("[[Bausteine]]")==0)
        {

            while (!f.eof())
            {
                getline(f,buffer);

                if(buffer=="\r")
                {
                    cout <<"leerzeile gefunden"<<endl;
                    break;
                }
                //"\r" entfernen
                buffer.erase(buffer.size()-1);

                GatterTyp* dummy= new GatterTyp();


                dummy->setName(buffer);

                bibElemente.push_back(*dummy);
            }
        }
        else if(buffer.find("[")==0)
        {

            string name = buffer.substr(1,buffer.size()-2);
            //sucht in bibElemente nach dem im Absatz gefundenen Element
            for (vector<GatterTyp>::iterator it = bibElemente.begin(); it!=bibElemente.end(); ++it)
            {
                if(it->getName()==name)
                {
                    cout <<it->getName()<<"=="<<name<<endl;

                    while (!f.eof())
                    {
                        getline(f,buffer);

                        if(buffer=="\r")
                        {
                            cout <<"leerzeile gefunden"<<endl;
                            break;
                        }
                        //"\r" entfernen
                        buffer.erase(buffer.size()-1);


                        if(buffer.find("ei:")==0){
                            it->setEingaenge(atoi(buffer.substr(4).c_str()));
                        }
                        if(buffer.find("ei:")==0){
                            it->setEingaenge(atoi(buffer.substr(4).c_str()));
                        }


                    }
                    break;
                }


                while (!f.eof())
                {
                    getline(f,buffer);
                    if(buffer=="\r")
                    {
                        cout <<"leerzeile gefunden"<<endl;
                        break;
                    }

                    cout <<"x "<<buffer<<endl;

                }
                cout <<endl;
            }

        }
    }


    for (vector<GatterTyp>::iterator it = bibElemente.begin(); it!=bibElemente.end(); ++it)
    {
        cout << it->getName() << endl;
    }
}
/**Speichert den Pfad zu Bibliotheksdatei im entsprechenden Attribut,
falls diese unter dem angegebenen Pfad vorhanden ist und sie geöﬀnet werden kann.
*/
bool Bibliothek::pfadEinlesen(string pfad)
{

    ifstream f(pfad.c_str());
    if(f.good())
    {
        datei = pfad;
        return true;
    }
    else
    {
        openError();
        return false;
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
