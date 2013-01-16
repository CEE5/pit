
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
GatterTyp* Bibliothek::getBibElement(string typ)
{

    for(int i=0;i< bibElemente.size();i++){
        if(bibElemente[i]->getName()==typ)
        {
            if(bibElemente[i]->getIsFlipflop()){
                return (dynamic_cast<Flipflop*>(bibElemente[i]));
            }
            else {
                return bibElemente[i];
            }
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
            cout << i<<": "<<buffer<<endl;
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
        buffer.erase(buffer.size()-1);

        //von [[Bausteine]] bis Leerzeile einlesen
        if(buffer.find("[[Bausteine]]")==0)
        {

            while (!f.eof())
            {
                getline(f,buffer);

                if(buffer=="\r")
                {

                    debug_msg("Blockende gefunden");
                    break;
                }

                //"\r" entfernen
                buffer.erase(buffer.size()-1);



                /*if(buffer =="dff")
                {
                    Flipflop* dummy = (new Flipflop());

                    dummy->setName(buffer);

                    bibElemente.push_back(*dummy);

                    debug_msg( "ff angelegt: "<<buffer);

                }
                else
                {
                    GatterTyp* dummy= new GatterTyp();
                    dummy->setName(buffer);

                    bibElemente.push_back(*dummy);
                    debug_msg( "gt angelegt: "<<buffer);

                }*/




            }
        }

        else if(buffer.find("[")==0)
        {
            //Kalmmern [ ] entfernen
            string name = buffer.substr(1,buffer.size()-2);


                //FF anlegen
                if(name=="dff")
                {
                    Flipflop *ff = new Flipflop();
                    ff->setName(name);

                    debug_msg(name <<"als FF anlegen");


                    while (!f.eof())
                    {
                        getline(f,buffer);

                        //Abbruch falls Absatz zu Ende
                        if(buffer=="\r")
                        {

                            //FF zu bibElemente hinzfügen
                             bibElemente.push_back((ff));




                            debug_msg("Ende von: "<<name<<" gefunden");
                            break;
                        }
                        //"\r" entfernen
                        buffer.erase(buffer.size()-1);



                        ///*allgemeine Attribute
                        if(buffer.find("ei:")==0)
                        {
                            ff->setEingaenge(atoi(buffer.substr(3).c_str()));
                            debug_msg( "ei init "<<ff->getEingaenge());
                        }

                        else if(buffer.find("cl:")==0)
                        {
                            ff->setLastKapazitaet(atoi(buffer.substr(3).c_str()));
                            debug_msg("cl init "<<ff->getLastKapazitaet());
                        }

                        else if(buffer.find("kl:")==0)
                        {
                            ff->setLastFaktor(atoi(buffer.substr(3).c_str()));
                            debug_msg("kl init "<<ff->getLastFaktor());
                        }

                        else if(buffer.find("tpd0:")==0)
                        {
                            ff->setGrundLaufzeit(atof(buffer.substr(5).c_str()));
                            debug_msg("tpd0 init "<<ff->getGrundLaufzeit());
                        }


                        ///*Flipflop Attribute
                        else if(buffer.find("tsetup:")==0)
                        {
                            ff->setSetupTime(atoi(buffer.substr(7).c_str()));
                            debug_msg("ff testup init: "<<ff->getSetupTime());

                        }
                        else if(buffer.find("ed:")==0)
                        {
                            ff->setEingaenge(atoi(buffer.substr(3).c_str()));
                            debug_msg("ff ed init: "<<ff->getEingaenge());

                        }
                        else if(buffer.find("thold:")==0)
                        {
                            ff->setHoldTime(atoi(buffer.substr(6).c_str()));
                            debug_msg("ff thold init: "<<ff->getHoldTime());

                        }
                        else if(buffer.find("cd:")==0)
                        {
                            ff->setLastKapazitaet(atoi(buffer.substr(3).c_str()));
                            debug_msg("ff cd init: "<<ff->getLastKapazitaet());

                        }
                        else if(buffer.find("tpdt:")==0)
                        {
                            ff->setGrundLaufzeit(atof(buffer.substr(5).c_str()));
                            debug_msg("ff tpdt init: "<<ff->getGrundLaufzeit());

                        }
                        else if(buffer.find("kl:")==0)
                        {
                            ff->setLastFaktor(atoi(buffer.substr(3).c_str()));
                            debug_msg("ff kl init: "<<ff->getLastFaktor());

                        }
                        else if(buffer.find("ct:")==0)
                        {
                            ff->setLastKapazitaetClock(atoi(buffer.substr(3).c_str()));
                            debug_msg("ff ct init: "<<ff->getLastKapazitaetClock());

                        }

                        else
                        {
                            if(buffer.find("#endf")!=0){
                                //Falls Attribut nicht gefunden
                                readError();
                                debug_msg(buffer<<" nicht gefunden");
                            }
                            else { bibElemente.push_back((ff));break;}
                        }

                    }


                }

                else{

                    GatterTyp *gt = new GatterTyp();

                    debug_msg(name <<"als GT anlegen");
                    gt->setName(name);



                                        while (!f.eof())
                    {
                        getline(f,buffer);

                        //Abbruch falls Absatz zu Ende
                        if(buffer=="\r")
                        {

                            //GT zu bibElemente hinzfügen
                            bibElemente.push_back(gt);





                            debug_msg("Ende von: "<<name<<" gefunden");
                            break;
                        }
                        //"\r" entfernen
                        buffer.erase(buffer.size()-1);



                        ///*allgemeine Attribute
                        if(buffer.find("ei:")==0)
                        {
                            gt->setEingaenge(atoi(buffer.substr(3).c_str()));
                            debug_msg( "ei init "<<gt->getEingaenge());
                        }

                        else if(buffer.find("cl:")==0)
                        {
                            gt->setLastKapazitaet(atoi(buffer.substr(3).c_str()));
                            debug_msg("cl init "<<gt->getLastKapazitaet());
                        }

                        else if(buffer.find("kl:")==0)
                        {
                            gt->setLastFaktor(atoi(buffer.substr(3).c_str()));
                            debug_msg("kl init "<<gt->getLastFaktor());
                        }

                        else if(buffer.find("tpd0:")==0)
                        {
                            gt->setGrundLaufzeit(atof(buffer.substr(5).c_str()));
                            debug_msg("tpd0 init "<<gt->getGrundLaufzeit());
                        }


                        else
                        {
                            if(buffer.find("#endf")!=0){
                                //Falls Attribut nicht gefunden
                                readError();
                                debug_msg(buffer<<" nicht gefunden");
                            }
                            else break;
                        }

                    }


                }

        }
    }



    for(int h=0;h<bibElemente.size();h++){
        debug_msg( bibElemente[h]->getName());
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
    cerr <<"OPEN ERROR"<<endl;

}
/**Ausgabe einer Fehlermeldung beim Lesen einer Datei.
*/
void Bibliothek::readError(void)
{
    cerr <<"READ ERROR"<<endl;

}
