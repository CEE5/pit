// GraphErzeuger.h
//
// Geruest

//#include "stdafx.h"
#include <iostream>
#include "SchaltwerkElement.h"
#include "ListenElement.h"
#include "Bibliothek.h"
#include "signals.h"

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

};
#endif
