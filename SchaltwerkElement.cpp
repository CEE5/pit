// SchaltwerkElement.cpp
//
//
//
// nachfolgerHinzufuegen (?)

#include "SchaltwerkElement.h"
#include "Bibliothek.h"




	/** Konstruktor der Klasse. Er soll beim Anlegen der Klasse alle Attribute mit dem Wert 0 bzw. NULL für Zeiger initialisieren. Außerdem
	bekommt der Konstruktor einen Zeiger auf ein Element der Bibliotheksdatenbank und speichert es in das Attribut typ.*/
	SchaltwerkElement::SchaltwerkElement(  GatterTyp* gTyp ){
		name = "";
		GatterTyp* typ = gTyp;
		laufzeitEinzelgatter = 0;
		nachfolgerElemente[0] = NULL; //schöner lösen?
		nachfolgerElemente[1] = NULL;
		nachfolgerElemente[2] = NULL;
		nachfolgerElemente[3] = NULL;
		nachfolgerElemente[4] = NULL;
		anzahlNachfolger = 0;
		isEingangsElement = false;
		isAusgangsElement = false;
		anzahlEingangssignale = 0;
	}

	/** Destruktor der Klasse.*/
	SchaltwerkElement::~SchaltwerkElement() { }


	/** Die folgenden Methoden dienen zum Lesen der privaten Attribute eines einzelnen Objekts vom Typ
    SchaltwerkElement.*/

	/** Lesen des privaten Attributes name eines einzelnen Objekts vom Typ SchaltwerkElement. */
	string SchaltwerkElement::getName(){
		return name;
	}

	/** Lesen des privaten Attributes typ eines einzelnen Objekts vom Typ SchaltwerkElement. */
	GatterTyp* SchaltwerkElement::getTyp(){
		return typ;
	}

	/** Lesen des privaten Attributes laufzeitEinzelgatter eines einzelnen Objekts vom Typ SchaltwerkElement. */
	double SchaltwerkElement::getLaufzeitEinzelgatter(){
		return laufzeitEinzelgatter;
	}

	/** Lesen des privaten Attributes nachfolgerElemente eines einzelnen Objekts vom Typ SchaltwerkElement. */
	SchaltwerkElement* SchaltwerkElement::getNachfolger( int pos){
		return nachfolgerElemente[pos];
	}

	/** Lesen des privaten Attributes anzahlNachfolger eines einzelnen Objekts vom Typ SchaltwerkElement. */
	int SchaltwerkElement::getAnzahlNachfolger(){
		return anzahlNachfolger;
	}

	/** Lesen des privaten Attributes anzahlEingangssignale eines einzelnen Objekts vom Typ SchaltwerkElement. */
	short SchaltwerkElement::getAnzahlEingangssignale(){
		return anzahlEingangssignale;
	}

	/** Lesen des privaten Attributes isEingangsElement eines einzelnen Objekts vom Typ SchaltwerkElement. */
	bool SchaltwerkElement::getIsEingangsElement(){
		return isEingangsElement;
	}

	/** Lesen des privaten Attributes isAusgangsElement eines einzelnen Objekts vom Typ SchaltwerkElement. */
	bool SchaltwerkElement::getIsAusgangsElement(){
		return isAusgangsElement;
	}

	/** Die folgenden  Methoden  dienen  zum  Schreiben  der  privaten  Attribute  eines  einzelnen  Objekts  vom  Typ
      SchaltwerkElement.*/
	void SchaltwerkElement::setName( string n){
		name = n;
	}

	void SchaltwerkElement::nachfolgerHinzufuegen( SchaltwerkElement *schaltwerkElement, int pos ){
		//
		nachfolgerElemente[pos] = schaltwerkElement;
		anzahlNachfolger++;
		//
	}
	void SchaltwerkElement::setAnzahlNachfolger( int anzahlN ){
		anzahlNachfolger = anzahlN;
	}
	void SchaltwerkElement::setAnzahlEingangssignale( short anzahlE ){
		anzahlEingangssignale = anzahlE;
	}
	void SchaltwerkElement::setIsEingangsElement( bool isEingangsEl ){
		isEingangsElement = isEingangsEl;
	}
	void SchaltwerkElement::setIsAusgangsElement( bool isAusgangsEl ){
		isAusgangsElement = isAusgangsEl;
	}
	void SchaltwerkElement::setLaufzeitEinzelgatter( double lzt ){
		laufzeitEinzelgatter = lzt;
	}
