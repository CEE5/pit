// ListenElement.h
//
//

#ifndef _ListenElement_
#define _ListenElement_

#include "SchaltwerkElement.h"


class ListenElement {
private:

	SchaltwerkElement* schaltwerkElement;
	ListenElement* next;

public:

	/** Konstruktor der Klasse. Er soll beim Anlegen der Klasse alle Zeiger-Attribute mit NULL initialisieren.*/
	ListenElement();

	/** Destruktor  der  Klasse.*/
	~ListenElement();

	/** Lesen des privaten Attributes schaltwerkElement eines einzelnen Objekts vom Typ ListenElement.*/
	SchaltwerkElement* getSchaltwerkElement();

	/** Lesen des privaten Attributes next eines einzelnen Objekts vom Typ ListenElement.*/
	ListenElement* getNextElement();

	/** Schreiben  des  privaten  Attributes schaltwerkElement eines  einzelnen  Objekts  vom  Typ ListenElement.*/
	void setSchaltwerkElement( SchaltwerkElement* SchaltwerkEl);

	/** Schreiben  des  privaten  Attributes next eines  einzelnen  Objekts  vom  Typ ListenElement.*/
	void setNextElement( ListenElement* nextEl);
};

#endif // _Listenelement_
