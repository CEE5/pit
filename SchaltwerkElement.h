// SchaltwerkElement.h
//
//

#ifndef _SchaltwerkElement_
#define _SchaltwerkElement_

#include "GatterTyp.h"
#include <string>


class SchaltwerkElement {
private:
	string				name;
	GatterTyp*			typ;
	double				laufzeitEinzelgatter;
	SchaltwerkElement*	nachfolgerElemente[5];
	int					anzahlNachfolger;
	bool				isEingangsElement;
	bool				isAusgangsElement;
	short				anzahlEingangssignale;

public:

	/** Konstruktor der Klasse. Er soll beim Anlegen der Klasse alle Attribute mit dem Wert 0 bzw. NULL für Zeiger initialisieren. Außerdem
	bekommt der Konstruktor einen Zeiger auf ein Element der Bibliotheksdatenbank und speichert es in das Attribut typ.*/
	SchaltwerkElement( GatterTyp* gTyp);
    ~SchaltwerkElement();                   /** Ist der Destruktor der Klasse.*/

	/** Die folgenden Methoden dienen zum Lesen der privaten Attribute eines einzelnen Objekts vom Typ
    SchaltwerkElement.*/

    string getName();                       /** Lesen des privaten Attributes name eines einzelnen Objekts vom Typ SchaltwerkElement. */
	GatterTyp* getTyp();                    /** Lesen des privaten Attributes typ eines einzelnen Objekts vom Typ SchaltwerkElement. */
    double getLaufzeitEinzelgatter();       /** Lesen des privaten Attributes laufzeitEinzelgatter eines einzelnen Objekts vom Typ SchaltwerkElement. */
	SchaltwerkElement* getNachfolger( int pos);  /** Lesen des privaten Attributes nachfolgerElemente eines einzelnen Objekts vom Typ SchaltwerkElement. */
	int getAnzahlNachfolger();              /** Lesen des privaten Attributes anzahlNachfolger eines einzelnen Objekts vom Typ SchaltwerkElement. */
	short getAnzahlEingangssignale();       /** Lesen des privaten Attributes anzahlEingangssignale eines einzelnen Objekts vom Typ SchaltwerkElement. */
	bool getIsEingangsElement();            /** Lesen des privaten Attributes isEingangsElement eines einzelnen Objekts vom Typ SchaltwerkElement. */
	bool getIsAusgangsElement();            /** Lesen des privaten Attributes isAusgangsElement eines einzelnen Objekts vom Typ SchaltwerkElement. */

	/** Die folgenden  Methoden  dienen  zum  Schreiben  der  privaten  Attribute  eines  einzelnen  Objekts  vom  Typ
      SchaltwerkElement.*/

	void setName( string n);                /**Schreiben  des  privaten  Attributes name eines  einzelnen  Objekts  vom  Typ SchaltwerkElement.*/
	void nachfolgerHinzufuegen( SchaltwerkElement* schaltwerkElement, int pos);  /**Schreiben  des  privaten  Attributes nachfolger eines  einzelnen  Objekts
                                                                                    vom  Typ SchaltwerkElement.*/
	void setAnzahlNachfolger( int anzahlN);         /**Schreiben  des  privaten  Attributes anzahlNachfolger eines  einzelnen  Objekts  vom  Typ SchaltwerkElement.*/
	void setAnzahlEingangssignale( short anzahlE);  /**Schreiben  des  privaten  Attributes anzahlEingangssignale eines  einzelnen  Objekts  vom  Typ SchaltwerkElement.*/
	void setIsEingangsElement(bool isEingangsEl);   /**Schreiben  des  privaten  Attributes isEingangsElement eines  einzelnen  Objekts  vom  Typ SchaltwerkElement.*/
	void setIsAusgangsElement(bool isAusgangsEl);   /**Schreiben  des  privaten  Attributes isAusgangsElement eines  einzelnen  Objekts  vom  Typ SchaltwerkElement.*/
	void setLaufzeitEinzelgatter(double lzt);       /**Schreiben  des  privaten  Attributes laufzeitEinzelgatter eines  einzelnen  Objekts  vom  Typ SchaltwerkElement.*/

};
#endif // _SchaltwerkElement_
