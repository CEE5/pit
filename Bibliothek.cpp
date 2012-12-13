#include "Bibliothek.h"

#define DEBUG_METHOD(name) std::cout << "DEBUG --> " << name<<endl;




Bibliothek::Bibliothek()
{
    vector<GatterTyp*> bibElemente;
    vector<Flipflop*> bibHilfe;
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
GatterTyp* Bibliothek::getBibElement(string typ)
{

    for (vector<GatterTyp*>::iterator it = bibElemente.begin(); it!=bibElemente.end(); ++it)
    {

        if((*it)->getName()==typ)
        {

            return (*it);
        }
    }
}

/**Ausgabe der Datei auf dem Bildschirm, dabei sollen die Zeilen durchnummeriert werden.
Dabei soll, falls die Datei nicht vorhanden ist oder ein Fehler beim Lesen auftritt,
das Programm nicht abstürzen, sondern eine Fehlermeldung ausgeben. */
void Bibliothek::dateiAusgabe(void)
{
    ifstream f(datei.c_str());

    string buffer;

    int i=0;

    if(f.good())
    {
        while (!f.eof())
        {
            getline(f,buffer);
            cout <<i<<": "<<buffer<<endl;
            i++;
        }
    }
    else
    {
        openError();
    }

}
/**Die Methode dient zum Einlesen und Auswerten der Bibliotheksdatei.
Dabei soll jeder in der Datei beschriebene Gattertyp in einem Element vom Typ
GatterTyp im Vektor bibElemente gespeichert werden. Die Reihenfolge ist
dabei nicht wichtig. Das Flipﬂop kann dabei am Namen erkannt werden, welcher als bekannt vorausgesetzt wird.
Das Flipﬂop wird in einem Element vom Typ Flipflop im Vektor bibElemente gespeichert. */
void Bibliothek::dateiAuswerten(void)
{
    ifstream f(datei.c_str());

    string buffer;
    while (!f.eof())
    {
        getline(f,buffer);
        //"\r" entfernen
        if(linuxzusatz == 1) {
            buffer.erase(buffer.size()-linuxzusatz);
            DEBUG_METHOD("\\r entfernt"<<endl);
            }

        //von [[Bausteine]] bis Leerzeile einlesen
        if(buffer.find("[[Bausteine]]")==0)
        {

            while (!f.eof())
            {
                getline(f,buffer);

                if((buffer=="\r")or(buffer==""))
                {

                    DEBUG_METHOD("Blockende gefunden"<<endl);
                    break;
                }

                //"\r" entfernen
                if(linuxzusatz == 1) {
                    buffer.erase(buffer.size()-linuxzusatz);
                }

                    Flipflop* dummy = (new Flipflop());

                    dummy->setName(buffer);

                    bibHilfe.push_back(dummy);

                    DEBUG_METHOD( "(Hilfs-)ff angelegt: "<<buffer);


            }
        }
        else if(buffer.find("[")==0)
        {
            //Klammern [ ] entfernen
            string name = buffer.substr(1,buffer.size()-2);

            //sucht in bibHilfe nach dem im Absatz gefundenen Element
            for (vector<Flipflop*>::iterator it = bibHilfe.begin(); it!=bibHilfe.end(); ++it)
            {
                //Element gefunden
                if((*it)->getName()==name)
                {
                    DEBUG_METHOD("Uebereinstimmung gefunden: "<<(*it)->getName()<<"=="<<name);


                    while (!f.eof())
                    {
                        getline(f,buffer);

                        //Abbruch falls Absatz zu Ende
                        if((buffer=="\r")or(buffer==""))
                        {
                            DEBUG_METHOD("Ende von: "<<name<<" gefunden"<<endl);
                            break;
                        }
                        //"\r" entfernen
                        if(linuxzusatz == 1) {
                            buffer.erase(buffer.size()-linuxzusatz);
                            DEBUG_METHOD("\\r nach "<<name<<" entfernt"<<endl);
                            }



                        ///*allgemeine Attribute
                        if(buffer.find("ei:")==0)
                        {
                            (*it)->setEingaenge(atoi(buffer.substr(3).c_str()));
                            DEBUG_METHOD( "ei init "<<(*it)->getEingaenge());
                        }

                        else if(buffer.find("cl:")==0)
                        {
                            (*it)->setLastKapazitaet(atoi(buffer.substr(3).c_str()));
                            DEBUG_METHOD("cl init "<<(*it)->getLastKapazitaet());
                        }

                        else if(buffer.find("kl:")==0)
                        {
                            (*it)->setLastFaktor(atoi(buffer.substr(3).c_str()));
                            DEBUG_METHOD("kl init "<<(*it)->getLastFaktor());
                        }

                        else if(buffer.find("tpd0:")==0)
                        {
                            (*it)->setGrundLaufzeit(atof(buffer.substr(5).c_str()));
                            DEBUG_METHOD("tpd0 init "<<(*it)->getGrundLaufzeit());
                        }


                        ///*Flipflop Attribute
                        else if(buffer.find("tsetup:")==0)
                        {
                        (*it)->setSetupTime(atoi(buffer.substr(7).c_str()));
                            DEBUG_METHOD("ff testup init: "<<(*it)->getSetupTime());

                        }
                        else if(buffer.find("ed:")==0)
                        {
                            (*it)->setEingaenge(atoi(buffer.substr(3).c_str()));
                            DEBUG_METHOD("ff ed init: "<<(*it)->getEingaenge());

                        }
                        else if(buffer.find("thold:")==0)
                        {
                            (*it)->setHoldTime(atoi(buffer.substr(6).c_str()));
                            DEBUG_METHOD("ff thold init: "<<(*it)->getHoldTime());

                        }
                        else if(buffer.find("cd:")==0)
                        {
                            (*it)->setLastKapazitaet(atoi(buffer.substr(3).c_str()));
                            DEBUG_METHOD("ff cd init: "<<(*it)->getLastKapazitaet());

                        }
                        else if(buffer.find("tpdt:")==0)
                        {
                            (*it)->setGrundLaufzeit(atof(buffer.substr(5).c_str()));
                            DEBUG_METHOD("ff tpdt init: "<<(*it)->getGrundLaufzeit());

                        }
                        else if(buffer.find("kl:")==0)
                        {
                            (*it)->setLastFaktor(atoi(buffer.substr(3).c_str()));
                            DEBUG_METHOD("ff kl init: "<<(*it)->getLastFaktor());

                        }
                        else if(buffer.find("ct:")==0)
                        {
                            (*it)->setLastKapazitaetClock(atoi(buffer.substr(3).c_str()));
                            DEBUG_METHOD("ff ct init: "<<(*it)->getLastKapazitaetClock());

                        }

                        else
                        {
                            if(buffer.find("#endf")!=0){
                                //Falls Attribut nicht gefunden
                                readError();
                                DEBUG_METHOD(buffer<<" nicht gefunden"<<endl);
                            }
                            else break;
                        }

                    }

                }

            }

        }
    }

    for (vector<Flipflop*>::iterator it = bibHilfe.begin(); it!=bibHilfe.end(); ++it){
                if ( (*it)->getName()!= "dff"){
                        GatterTyp* tmpGatter = *it;
                        bibElemente.push_back(tmpGatter );
                        DEBUG_METHOD("gt angelegt: "<<tmpGatter->getName());
                        //DEBUG_METHOD("bibhilfegroesse: "<< bibHilfe.size());
                        //DEBUG_METHOD("bibelementegroesse: "<< bibElemente.size());
                } else {
                    bibElemente.push_back(*it);
                    DEBUG_METHOD("ff angelegt: "<< (*it)->getName());

                }
    }
    //Ausgabe aller angelegten Elemente
    for (vector<GatterTyp*>::iterator it = bibElemente.begin(); it!=bibElemente.end(); ++it)
    {
        DEBUG_METHOD("alle gt: "<<(*it)->getName());
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
        bibElemente.clear();
        return true;
    }
    else
    {
        //openError();
        return false;
    }

}

/**Ausgabe einer Fehlermeldung beim Öﬀnen einer Datei. */
void Bibliothek::openError(void)
{
    cerr <<"OPEN ERROR"<<endl;

}
/**Ausgabe einer Fehlermeldung beim Lesen einer Datei.
*/
void Bibliothek::readError(void)
{
    cerr <<"READ ERROR"<<endl;

}
