#include "Bibliothek.h"

#define DEBUG 1

#ifdef DEBUG
    #define DEBUG_METHOD(name) std::cout << "DEBUG-->" << name<<endl;
#else
    #define DEBUG_METHOD(name) ;
#endif



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
GatterTyp* Bibliothek::getBibElement(string typ)
{
     for (vector<GatterTyp>::iterator it = bibElemente.begin(); it!=bibElemente.end(); ++it)
            {
                if(it->getName()==typ){

                    return &(*it);
                }
            }
}

/**Ausgabe der Datei auf dem Bildschirm, dabei sollen die Zeilen durchnummeriert werden.
Dabei  soll,  falls  die  Datei  nicht  vorhanden  ist  oder  ein  Fehler  beim  Lesen  auftritt,
das Programm nicht abstürzen, sondern eine Fehlermeldung ausgeben. */
void Bibliothek::dateiAusgabe(void)
{
    ifstream f(datei.c_str());
    int i=0;
    string buffer;
    while (!f.eof())
    {
        cout <<i<<": "<<getline(f,buffer);
        i++;
    }

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

                    DEBUG_METHOD("leerzeile gefunden");
                    break;
                }

                //"\r" entfernen
                buffer.erase(buffer.size()-1);



                if(buffer =="dff")
                {
                    Flipflop* dummy = (new Flipflop());

                    dummy->setName(buffer);

                    bibElemente.push_back(*dummy);

                    DEBUG_METHOD( "ff angelegt: "<<buffer);

                }
                else
                {
                    GatterTyp* dummy= new GatterTyp();
                    dummy->setName(buffer);

                    bibElemente.push_back(*dummy);
                    DEBUG_METHOD( "gt angelegt: "<<buffer);

                }




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
                    DEBUG_METHOD(it->getName()<<"=="<<name);

                    while (!f.eof())
                    {
                        getline(f,buffer);

                        if(buffer=="\r")
                        {
                            DEBUG_METHOD("Ende von: "<<name<<" gefunden");
                            break;
                        }
                        //"\r" entfernen
                        buffer.erase(buffer.size()-1);


                        {
                            //allgemeine Attribute
                            if(buffer.find("ei:")==0)
                            {
                                it->setEingaenge(atoi(buffer.substr(3).c_str()));
                                DEBUG_METHOD( "ei init "<<it->getEingaenge());
                            }

                            else if(buffer.find("cl:")==0)
                            {
                                it->setLastKapazitaet(atoi(buffer.substr(3).c_str()));
                                DEBUG_METHOD("cl init "<<it->getLastKapazitaet());
                            }

                            else if(buffer.find("kl:")==0)
                            {
                                it->setLastFaktor(atoi(buffer.substr(3).c_str()));
                                DEBUG_METHOD("kl init "<<it->getLastFaktor());
                            }

                            else if(buffer.find("tpd0:")==0)
                            {
                                it->setGrundLaufzeit(atof(buffer.substr(5).c_str()));
                                DEBUG_METHOD("tpd0 init "<<it->getGrundLaufzeit());
                            }




                            else if(buffer.find("tsetup:")==0)
                            {
                                ((Flipflop*)&it )->setSetupTime(atoi(buffer.substr(7).c_str()));
                                DEBUG_METHOD("ff testup init: "<<((Flipflop*)&it )->getSetupTime());

                            }
                            else if(buffer.find("ed:")==0)
                            {
                                ((Flipflop*)&it )->setEingaenge(atoi(buffer.substr(3).c_str()));
                                DEBUG_METHOD("ff ed init: "<<((Flipflop*)&it )->getEingaenge());

                            }
                            else if(buffer.find("thold:")==0)
                            {
                                ((Flipflop*)&it )->setHoldTime(atoi(buffer.substr(6).c_str()));
                                DEBUG_METHOD("ff thold init: "<<((Flipflop*)&it )->getHoldTime());

                            }
                            else if(buffer.find("cd:")==0)
                            {
                                ((Flipflop*)&it )->setLastKapazitaet(atoi(buffer.substr(3).c_str()));
                                DEBUG_METHOD("ff cd init: "<<((Flipflop*)&it )->getLastKapazitaet());

                            }
                            else if(buffer.find("tpdt:")==0)
                            {
                                ((Flipflop*)&it )->setGrundLaufzeit(atof(buffer.substr(5).c_str()));
                                DEBUG_METHOD("ff tpdt init: "<<((Flipflop*)&it )->getGrundLaufzeit());

                            }
                            else if(buffer.find("kl:")==0)
                            {
                                ((Flipflop*)&it )->setLastFaktor(atoi(buffer.substr(3).c_str()));
                                DEBUG_METHOD("ff kl init: "<<((Flipflop*)&it )->getLastFaktor());

                            }
                            else if(buffer.find("ct:")==0)
                            {
                                ((Flipflop*)&it )->setLastKapazitaetClock(atoi(buffer.substr(3).c_str()));
                                DEBUG_METHOD("ff ct init: "<<((Flipflop*)&it )->getLastKapazitaetClock());

                            }

                            else
                            {
                                readError();
                            }

                        }






                    }
                    break;
                }


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

