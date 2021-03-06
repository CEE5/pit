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
    startElement = NULL;///Initialisierung
    endElement = NULL;
    signale = NULL;
    anzahlSignale = 0;
    gAnzahl = 0;

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
            debug_msg("INFO: eingang gefunden");
            eingaenge++;
        }
        else if (tmpSignal.getSignalTyp() == clk)         /// prueft ob Takt
        {
            debug_msg("INFO: clock gefunden");
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
                    debug_msg("INFO: ausgang gefunden");
                    ausgaenge++;
                }

                /// verknuepfen von Schaltwerkselement mit Listenelement
                newListenElement->setSchaltwerkElement( newSchaltwerkElement );
                gAnzahl++;
                debug_msg("INFO: "<<gAnzahl<<". ListenElement angelegt vom Typ "<< tmpSignal.getQuellenTyp()<<" !");


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
                cout << "Fehler! Unbenutztes Signal gefunden" << endl;
                cin.ignore();
                cin.get();
            }
        }

        else            // von Signaltypabfrage
        {
            cout << "Fehler! Unbekannter Signaltyp" << endl;
            cin.ignore();
            cin.get();
        }
    }
    /// eingang finden
    for (int z = 0; z < signallist.getAnzahlSignale(); z++)                /// geht die Sigalliste durch
    {
        if ( signallist.getSignal(z)->getSignalTyp() == eingang)            /// vergleicht mit Signaltypen, ob "eingang" der Signaltyp ist
        {
            debug_msg( "INFO: Dieses Eingangssignal hat "<<signallist.getSignal(z)->getAnzahlZiele()<< " Ziel(e)");
            for ( int y = 0; y < signallist.getSignal(z)->getAnzahlZiele(); y++)               /// durchlaeuft alle ziele dieses signals
            {
                string eingangsGatter = signallist.getSignal(z)->getZiel( y );
                for (ListenElement* ptr = startElement; ptr != NULL; ptr = ptr->getNextElement())   /// und gleicht die ziele mit den schaltwerksnamen in dem
                {
                    if ( ptr->getSchaltwerkElement()->getName() == eingangsGatter )                 /// jeweiligen listenelement ab
                    {
                        ptr->getSchaltwerkElement()->setIsEingangsElement(true);
                        debug_msg( "INFO: "<< ptr->getSchaltwerkElement()->getName() <<" ist Eingang");
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

        debug_msg("INFO:-----");

        for (int z = 0; z < signallist.getAnzahlSignale(); z++)         ///danach die Signalliste
        {
            for (int r = 0; r < signallist.getSignal(z)->getAnzahlZiele(); r++)     /// und die Ziele eines jeden Signals
            {

                /// prueft, ob das Signalziel mit dem SchaltwerkElementsnamen uebereinstimmt und erhoeht den Eingangszaehler bei Erfolg um 1
                if ( signallist.getSignal(z)->getZiel(r) == ptr->getSchaltwerkElement()->getName())
                {
                    tmpZaehler += 1;

                    debug_msg("INFO: "<< tmpZaehler <<". Eingang von "<< ptr->getSchaltwerkElement()->getName() <<" gefunden");
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
            cout << "Fehler!\nAnzahl Eingaenge laut Bibliothek: \t"<<ptr->getSchaltwerkElement()->getTyp()->getEingaenge()<<endl
            <<"Anzahl Eingaenge laut Schaltwerk: \t"<<tmpZaehler << endl;
            cin.ignore();
            cin.clear();
            cin.get();
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
                                debug_msg( "INFO: "<< tmpListenElement2->getSchaltwerkElement()->getName() << " ist Nachfolger von " << tmpListenElement->getSchaltwerkElement()->getName());
                            }
                        }
                    }

                }

            }

        }
        else          // von Anzahlnachfolger if-Abfrage
        {
            cout << "Fehler: Mehr als 5 Nachfolgegatter bei "<< tmpSWE->getName() << endl;
        }

    }

}

void GraphErzeuger::listenAusgabe ( )         /// gibt die Listenelemente mit Gatternamen und ihre NachfolgeGatter aus
{

    for ( ListenElement* ptr = startElement; ptr != NULL; ptr = ptr->getNextElement())  /// geht die ListenElemente durch
    {

        cout << "-----------\n"<<endl
        <<"Gattername:  \t\t" <<  ptr->getSchaltwerkElement()->getName() <<endl                  /// Gattername
        <<"Gattertyp:  \t\t" << ptr->getSchaltwerkElement()->getTyp()->getName() <<endl;         /// GatterTyp

        /// evtle zusaetzliche Ausgaben wie "Eingang", "Ausgang", "LaufzeitEinzelGatter", fuer FlipFlops noch andere Attribute
        if ( ptr->getSchaltwerkElement()->getIsEingangsElement() == true)         // kann man sich mal noch ueberlegen in die Ausgabe mit aufzunehmen
        {
            cout <<"Schaltungseingangselement"<<endl;
        }
        if ( ptr->getSchaltwerkElement()->getIsAusgangsElement() == true)
        {
            cout<<"Schaltungsausgangselement"<< endl;
        }
        cout<<"Laufzeit Einzelgatter: \t"<< ptr->getSchaltwerkElement()->getLaufzeitEinzelgatter() <<endl;

            cout << "Is Flipflop: \t\t"<< (( Flipflop*) (ptr->getSchaltwerkElement()->getTyp()) )->getIsFlipflop()<<endl;

        if (ptr->getSchaltwerkElement()->getTyp()->getName()== "dff")
        {
           cout << "Setup-Time: \t\t" << (( Flipflop*) (ptr->getSchaltwerkElement()->getTyp()) )->getSetupTime() << endl
            << "Hold-Time \t\t" << (( Flipflop*) (ptr->getSchaltwerkElement()->getTyp()) )->getHoldTime()<<endl
            << "Lastkapazitaet: \t"<< (( Flipflop*) (ptr->getSchaltwerkElement()->getTyp()) )->getLastKapazitaetClock()<<endl;
        }

        cout<<"Anzahl Eingangssignale: "<< ptr->getSchaltwerkElement()->getAnzahlEingangssignale() <<endl;        // Ende Fakultative Ausgabe

        /// Ausgabe der Anzahl der Folgegatter und dann der Gatter mit ihrem Namen
        if (ptr->getSchaltwerkElement()->getAnzahlNachfolger()==1){
            cout<<"--->Das Gatter hat "<< ptr->getSchaltwerkElement()->getAnzahlNachfolger()<<" Ziel" <<endl;  /// Einzahl
        }else if(ptr->getSchaltwerkElement()->getAnzahlNachfolger()==0){
            cout<<"--->Das Gatter hat keine Ziele" <<endl;                                                     /// Keine
        }else{
            cout<<"--->Das Gatter hat "<< ptr->getSchaltwerkElement()->getAnzahlNachfolger()<<" Ziele" <<endl; /// Mehrzahl
        }

        if (ptr->getSchaltwerkElement()->getAnzahlNachfolger()!=0) /// falls Nachfolger existieren
        {

            string ausgabe = " ";
            for ( int s = 0; s < ptr->getSchaltwerkElement()->getAnzahlNachfolger() ; s++)  /// werden alle Nachfolgernamen in einen Ausgabe string geschrieben
            {

                ausgabe = ausgabe  + ptr->getSchaltwerkElement()->getNachfolger(s)->getName() + " ";
            }
            cout << "Angeschlossene Gatter:\t"<<ausgabe <<endl;
        }
        else /*if (ptr->getSchaltwerkElement()->getAnzahlNachfolger()==0)*/ /// falls keine Nachfolger existieren
        {
            cout << ptr->getSchaltwerkElement()->getName() << " hat keine Folgegatter"<<endl;
        }

    }
}



