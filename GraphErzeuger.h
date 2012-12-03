// GraphErzeuger.h
//
//

#ifndef _GraphErzeuger_
#define _GraphErzeuger_

//#include "stdafx.h"
#include <iostream>
#include "SchaltwerkElement.h"
#include "ListenElement.h"
#include "Bibliothek.h"
#include "signals.h"
#include "SignalListeErzeuger.h"


class GraphErzeuger {
private:
	Bibliothek* bibliothek;
	ListenElement* startElement;
	ListenElement* endElement;
	Signal* signale;
	short anzahlSignale;

public:
	GraphErzeuger();          /// Konstruktor; initialisiert alle variablen mit NULL bzw 0
	~GraphErzeuger();          /// unnuetzer Destruktor

    void listeAnlegen( SignalListeErzeuger signallist);     /** durchlaeuft die SignalListe, weisst jeder Quelle ein Schaltwerk zu, uebernimmt Eigenschaften der
                                                            Signale und Gattertypen und verknuepft die Schaltwerke mit je einem Listenelement und die ListenElemente
                                                            untereinander */
    void graphErzeugen( SignalListeErzeuger signallist);    /** durchlaeuft oben angelegte Liste und verknuepft auf Grundlage der Signalliste die Schaltwerke
                                                            miteinander */
    void listenAusgabe ( );     // bisher nur zum testen /// gibt die Liste mit den Schaltwerkinfos aus inkl der von graphErzeugen gefundenen Adjazenzbeziehungen

    void setBibliothek( Bibliothek* biblio); /// liest eine Bauteilbibliothek ein
    Bibliothek* getBibliothek();            /// gibt die gespeicherte Bib zurueck /*(ungebraucht)*/

    /*ListenElement* getStartElement(); //braucht man nicht
    void setStartElement( ListenElement* start);

    ListenElement* getEndElement();
    void setEndElement( ListenElement* ende);*/
};
#endif // _GraphErzeuger_
