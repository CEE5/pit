// GraphErzeuger.h
//
// Geruest

//#include "stdafx.h"
#include <iostream>
#include "SchaltwerkElement.h"
#include "ListenElement.h"
#include "Bibliothek.h"
#include "signals.h"
#include "SignalListeErzeuger.h"

#ifndef _GraphErzeuger_
#define _GraphErzeuger_

class GraphErzeuger {
private:
	Bibliothek* bibliothek;
	ListenElement* startElement;
	ListenElement* endElement;
	Signal* signale;
	short anzahlSignale;

public:
	GraphErzeuger();
	~GraphErzeuger();
	// blabla

    void graphErzeugen( SignalListeErzeuger signallist);

    Bibliothek* getBibliothek();

    /*ListenElement* getStartElement();
    void setStartElement( ListenElement* start);

    ListenElement* getEndElement();
    void setEndElement( ListenElement* ende);*/

    void setBibliothek( Bibliothek biblio);

    void listenAusgabe ( );

};
#endif
