// GraphErzeuger.cpp
//
//

#include "GraphErzeuger.h"

// richtige ausgabe schreiben

GraphErzeuger::GraphErzeuger()
{
    bibliothek = NULL;
    startElement = NULL;
    endElement = NULL;
    signale = NULL;
    anzahlSignale = 0;
}


/** Destruktor der Klasse.*/
GraphErzeuger::~GraphErzeuger()
{

}

Bibliothek* GraphErzeuger::getBibliothek()
{
    return bibliothek;
}

void GraphErzeuger::setBibliothek( Bibliothek* biblio)
{
    bibliothek = biblio;
}

ListenElement* GraphErzeuger::getStartElement(){
    return startElement;
}

void GraphErzeuger::setStartElement( ListenElement* start){
    startElement = start;
}

ListenElement* GraphErzeuger::getEndElement(){
    return endElement;
}

void GraphErzeuger::setEndElement( ListenElement* ende){
    endElement = ende;
}

int GraphErzeuger::getGatterAnzahl(){
    return gAnzahl;
}

void GraphErzeuger::listeAnlegen(SignalListeErzeuger signallist)
{

    gAnzahl = 0;        // sind bisher nur zum INFO ausgeben da
    short eingaenge = 0;
    short ausgaenge = 0;

    ListenElement* tmpElement = NULL;
    anzahlSignale = signallist.getAnzahlSignale();

/// geht Signalliste durch
    for (int i = 0; i < anzahlSignale; i++)
    {
        Signal tmpSignal = *signallist.getSignal( i );

        if ((tmpSignal.getSignalTyp() == eingang) )         /// prueft ob Eingang
        {
            cout <<"INFO: eingang gefunden"<<endl;
            eingaenge++;
        }
        else if (tmpSignal.getSignalTyp() == clk)         /// prueft ob Takt
        {
            cout <<"INFO: clock gefunden"<<endl;
        }
        else if ((tmpSignal.getSignalTyp() == intern) or (tmpSignal.getSignalTyp() == ausgang))   /// wenn intern oder ausgangs-signal hat das signal eine quelle,
        {
            /// die man in Schaltwerke ueberfuehren kann
            if ( tmpSignal.getQuelle() != "" )          /// zum abfangen von unbenutzten Signalen
            {
                GatterTyp* tmpGatter = bibliothek->getBibElement(tmpSignal.getQuellenTyp());  // kann man sich theoretisch auch sparen und alle tmpGatter durch bibliothek->getBibElement(tmpSignal.getQuellenTyp()) ersetzen

                ListenElement* newListenElement = new ListenElement();
                SchaltwerkElement* newSchaltwerkElement = new SchaltwerkElement( tmpGatter );

                /// Schaltwerk uebernimmt Daten des Signals
                newSchaltwerkElement->setName(tmpSignal.getQuelle());
                newSchaltwerkElement->setAnzahlNachfolger(tmpSignal.getAnzahlZiele());
                newSchaltwerkElement->setLaufzeitEinzelgatter( tmpGatter->getGrundLaufzeit() );
                newSchaltwerkElement->setAnzahlEingangssignale( tmpGatter->getEingaenge());

                /// pruefen ob Ausgang
                if ( tmpSignal.getSignalTyp() == ausgang )
                {
                    newSchaltwerkElement->setIsAusgangsElement(true);
                    cout <<"INFO: ausgang gefunden"<<endl;
                    ausgaenge++;
                }

                /// verknuepfen von Schaltwerkselement mit Listenelement
                newListenElement->setSchaltwerkElement( newSchaltwerkElement );
                gAnzahl++;
                cout <<"INFO: "<<gAnzahl<<". ListenElement angelegt vom Typ "<< tmpSignal.getQuellenTyp()<<" !"<<endl;


                /// baut die Liste auf
                if ( startElement == NULL )  /// ist nur NULL,wenn noch kein Element der Liste existiert
                {
                    endElement = newListenElement;
                    startElement = newListenElement;

                }
                else
                {
                    tmpElement->setNextElement( newListenElement );
                    endElement = newListenElement;
                }
                tmpElement = newListenElement;

            }
            else   // von leerer Quelle Abfrage, um ungenutzte Signake zu erkennen
            {
                cerr << "Fehler! Unbenutztes Signal gefunden"<<endl;
            }
        }

        else            // von Signaltypabfrage
        {
            cerr << "Fehler! Unbekannter Signaltyp" <<endl;
        }
    }
    /// eingang finden
    for (int z = 0; z < signallist.getAnzahlSignale(); z++)                /// geht die Sigalliste durch
    {
        if ( signallist.getSignal(z)->getSignalTyp() == eingang)            /// vergleicht mit Signaltypen, ob "eingang" der Signaltyp ist
        {
            cout << "INFO: Dieses Eingangssignal hat "<<signallist.getSignal(z)->getAnzahlZiele()<< " Ziel(e)"<<endl;
            for ( int y = 0; y < signallist.getSignal(z)->getAnzahlZiele(); y++)               /// durchlaeuft alle ziele dieses signals
            {
                string eingangsGatter = signallist.getSignal(z)->getZiel( y );
                for (ListenElement* ptr = startElement; ptr != NULL; ptr = ptr->getNextElement())   /// und gleicht die ziele mit den schaltwerksnamen in dem
                {
                    if ( ptr->getSchaltwerkElement()->getName() == eingangsGatter )                 /// jeweiligen listenelement ab
                    {
                        ptr->getSchaltwerkElement()->setIsEingangsElement(true);
                        cout << "INFO: "<< ptr->getSchaltwerkElement()->getName() <<" ist Eingang"<<endl;
                    }
                }
            }
        }
    }

    /// prueft, ob es unbeschaltete Eingaenge gibt
    short tmpZaehler ;
    for (ListenElement* ptr = startElement; ptr != NULL; ptr = ptr->getNextElement())   /// durchlaeuft die Listenelemente
    {
        tmpZaehler = 0;

        cout <<"INFO:-----"<<endl;

        for (int z = 0; z < signallist.getAnzahlSignale(); z++)         ///danach die Signalliste
        {
            for (int r = 0; r < signallist.getSignal(z)->getAnzahlZiele(); r++)     /// und die Ziele eines jeden Signals
            {

                /// prueft, ob das Signalziel mit dem SchaltwerkElementsnamen uebereinstimmt und erhoeht den Eingangszaehler bei Erfolg um 1
                if ( signallist.getSignal(z)->getZiel(r) == ptr->getSchaltwerkElement()->getName())
                {
                    tmpZaehler += 1;

                    cout <<"INFO: "<< tmpZaehler <<". Eingang von "<< ptr->getSchaltwerkElement()->getName() <<" gefunden"<<endl;
                }
            }
        }
        /// falls dff mit clk, hat die Bib einen Eingang zu wenig, wird hier korrigiert
        if (ptr->getSchaltwerkElement()->getTyp()->getName()=="dff")  // weil der clock eingang nicht mit eingelesen wird.. sollte man vlt noch aendern
        {
            tmpZaehler -= 1;
        }
        /// check, ob Schaltwerk und Bib fuer das jeweilige Element dieselbe Anzahl Eingaenge verzeichnet haben
        if (ptr->getSchaltwerkElement()->getTyp()->getEingaenge() != tmpZaehler)
        {
            cerr << "Fehler!\nAnzahl Eingaenge laut Bibliothek: \t"<<ptr->getSchaltwerkElement()->getTyp()->getEingaenge()<<endl
            <<"Anzahl Eingaenge laut Schaltwerk: \t"<<tmpZaehler<<endl;
        }
    }

}


void GraphErzeuger::graphErzeugen(SignalListeErzeuger signallist)
{
    /// durchlaeuft die Liste der durch ListenElemente verknuepften Schaltwerke
    for (ListenElement* ptr = startElement; ptr != NULL; ptr = ptr->getNextElement())
    {
        ListenElement* tmpListenElement = ptr;
        SchaltwerkElement* tmpSWE = tmpListenElement->getSchaltwerkElement();

        /// prueft ob ein Schaltwerk maximal 5 Nachfolger besitzt
        if ( tmpSWE->getAnzahlNachfolger() <= 5)
        {

            /// durchlaeuft die Signalliste auf der Suche nach gleichnamigen Quellen der Signale und Schaltwerksnamen
            for (int i = 0; i < signallist.getAnzahlSignale(); i++)
            {

                Signal tmpSignal = *signallist.getSignal( i );

                if ( tmpSignal.getQuelle() == tmpSWE->getName())
                {

                    /// bei Treffer wird wieder die Signalliste durchlaufen auf der Suche nach den Zielen des gleichnamigen Signals
                    for ( int j = 0; j < tmpSignal.getAnzahlZiele(); j++)
                    {
                        string folgeGatter = tmpSignal.getZiel( j );

                        /// sucht zu den Zielen des Signals das entsprechende Schaltwerk aus den ListenElementen
                        for (ListenElement* ptr2 = startElement; ptr2 != NULL; ptr2 = ptr2->getNextElement())
                        {
                            ListenElement* tmpListenElement2 = ptr2;
                            if ( tmpListenElement2->getSchaltwerkElement()->getName() == folgeGatter )
                            {
                                tmpListenElement->getSchaltwerkElement()->nachfolgerHinzufuegen( tmpListenElement2->getSchaltwerkElement(), j );
                                cout << "INFO: "<< tmpListenElement2->getSchaltwerkElement()->getName() << " ist Nachfolger von " << tmpListenElement->getSchaltwerkElement()->getName()<<endl;
                            }
                        }
                    }

                } /*else{


                    }*/

            }

        }
        else          // von Anzahlnachfolger if-Abfrage
        {
            cerr << "Fehler: Mehr als 5 Nachfolgegatter bei "<< tmpSWE->getName() << endl;
        }

    }

}


void GraphErzeuger::listenAusgabe ( )              //bisher nur zum testen
{

    for ( ListenElement* ptr = startElement; ptr != NULL; ptr = ptr->getNextElement())
    {
        //SchaltwerkElement* tmpSWE = ptr->getSchaltwerkElement();
        cout << "----------"<<endl
        <<"Gattername: \t\t" <<  ptr->getSchaltwerkElement()->getName() <<endl
        <<"Gattertyp: \t\t" << ptr->getSchaltwerkElement()->getTyp()->getName() <<endl;

        if ( ptr->getSchaltwerkElement()->getIsEingangsElement() == true)
        {
            cout <<"Schaltungseingangselement"<<endl;
        }
        if ( ptr->getSchaltwerkElement()->getIsAusgangsElement() == true)
        {
            cout<<"Schaltungsausgangselement"<< endl;
        }
        cout<<"Laufzeit Einzelgatter: \t"<< ptr->getSchaltwerkElement()->getLaufzeitEinzelgatter() <<endl;

        if (ptr->getSchaltwerkElement()->getTyp()->getName()== "dff")
        {
            cout << "Is Flipflop: \t\t"<< (( Flipflop*) (ptr->getSchaltwerkElement()->getTyp()) )->getIsFlipflop()<<endl//;
            << "Setup-Time: \t\t" << (( Flipflop*) (ptr->getSchaltwerkElement()->getTyp()) )->getSetupTime() << endl
            << "Hold-Time \t\t" << (( Flipflop*) (ptr->getSchaltwerkElement()->getTyp()) )->getHoldTime()<<endl
            << "Lastkapazitaet: \t"<< (( Flipflop*) (ptr->getSchaltwerkElement()->getTyp()) )->getLastKapazitaetClock()<<endl;
        }

        cout<<"Anzahl Eingangssignale: "<< ptr->getSchaltwerkElement()->getAnzahlEingangssignale() <<endl;
        cout<<"Anzahl Nachfolger: \t"<< ptr->getSchaltwerkElement()->getAnzahlNachfolger() <<endl;
        if (ptr->getSchaltwerkElement()->getAnzahlNachfolger()!=0)
        {

            string ausgabe = " ";
            for ( int s = 0; s < ptr->getSchaltwerkElement()->getAnzahlNachfolger() ; s++)
            {

                ausgabe = ausgabe  + ptr->getSchaltwerkElement()->getNachfolger(s)->getName() + " ";
            }
            cout << "Folgegatter:"<<ausgabe <<endl;
        }
        else /*if (ptr->getSchaltwerkElement()->getAnzahlNachfolger()==0)*/
        {
            cout << ptr->getSchaltwerkElement()->getName() << " hat keine Folgegatter"<<endl;
        }

    }
}
