// ListenElement.cpp
//
//

#include "ListenElement.h"

/** Konstruktor der Klasse. Er soll beim Anlegen der Klasse alle Zeiger-Attribute mit NULL initialisieren.*/
ListenElement::ListenElement(){
	schaltwerkElement = NULL;
	next = NULL;
}

/** Destruktor  der  Klasse.*/
ListenElement::~ListenElement() { }

/** Lesen des privaten Attributes schaltwerkElement eines einzelnen Objekts vom Typ ListenElement.*/
SchaltwerkElement* ListenElement::getSchaltwerkElement(){
	return schaltwerkElement;
}

/** Lesen des privaten Attributes next eines einzelnen Objekts vom Typ ListenElement.*/
ListenElement* ListenElement::getNextElement(){
	return next;
}

/** Schreiben  des  privaten  Attributes schaltwerkElement eines  einzelnen  Objekts  vom  Typ ListenElement.*/
void ListenElement::setSchaltwerkElement( SchaltwerkElement* SchaltwerkEl){
	schaltwerkElement = SchaltwerkEl;
}

/** Schreiben  des  privaten  Attributes next eines  einzelnen  Objekts  vom  Typ ListenElement.*/
void ListenElement::setNextElement( ListenElement* nextEl){
	next = nextEl;
}
