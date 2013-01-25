//Faktoren.h
//
//


#ifndef _Faktoren_
#define _Faktoren_

class Faktoren {
    private:

	double	spannung,
			temp,
			spannungFaktor,
			tempFaktor,
			prozessFaktor;
	short	prozess;

	/** Beinhaltet die Werte Spannungstabelle in Form eines 2-dimensionalen Arrays. überprüft anhand des Arrays, ob der Wert vom Attribut spannung innerhalb
	der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zurück gegeben. Ansonsten wird die private Methode
	berechneFaktor() mit dem Wert, dem Array und der Grösse des Arrays als übergabeparameter aufgerufen. Der Rückgabewert der Methode berechneFaktor() wird in dem
	Attribut spannungFaktor gespeichert.*/
	bool berechneSpannungFaktor (double spannung);

	/** Beinhaltet die Werte Temperaturtabelle in Form eines 2-dimensionalen Arrays. überprüft anhand des Arrays, ob der Wert vom Attribut temp innerhalb
	der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zurück gegeben. Ansonsten wird die private Methode
	berechneFaktor() mit dem Wert, dem Array und der Grösse des Arrays als übergabeparameter aufgerufen. Der Rückgabewert der Methode berechneFaktor() wird in dem
	Attribut tempFaktor gespeichert. */
	bool berechneTempFaktor (double temp);

	/** Beinhaltet die Werte Prozesstablle in Form eines 2-dimensionalen Arrays. überprüft anhand des Arrays, ob der Wert vom Attribut prozess innerhalb
	der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zurück gegeben. Ansonsten wird die private Methode
	berechneFaktor() mit dem Wert, dem Array und der Grösse des Arrays als übergabeparameter aufgerufen. Der Rückgabewert der Methode berechneFaktor() wird in dem
	Attribut prozessFaktor gespeichert.*/
	bool berechneProzessFaktor (short prozess);

	/** Die Methode durchsucht das übergebene Array nach dem übergebenen Wert. Wenn der Wert im Array vorhanden ist (1. Spalte der Tabelle) wird der zugehörige
	Faktor (2. Spalte der Tabelle) direkt zurückgegeben, ansonsten wird mit den am nächsten liegenden Punkten eine Interpolation über die entsprechende Methode
	gestartet und der interpolierte Wert zurückgegeben. */
	double berechneFaktor (double wert, double arr[][2], int laenge);

	/** Diese Methode interpoliert einen Wert zwischen zwei vorgegebenen Punkten im 2D-Raum. Dabei bestimmen x1,
	y1 und x2, y2 jeweils die Koordinaten der zwei Punkte zwischen denen interpoliert werden soll. Der
	übergabeparameter wert bestimmt den x-Wert des gesuchten Wertes, dabei gilt x1 < wert < x2.*/
	double interpolation ( double wert, double x1, double x2, double y1, double y2);

public:

	/** Konstruktor der Klasse. Er soll beim Anlegen der Klasse alle Attribute mit dem Wert 0 initialisieren.*/
	Faktoren();

	/** Destruktor der Klasse. */
	~Faktoren();

	/** Diese Methode dient zum Lesen des privaten Attributes spannung */
	double getSpannung();

	/** Diese Methode dient zum Lesen des privaten Attributes temp (die Temperatur) */
	double getTemp();

	/** Diese Methode dient zum Lesen des privaten Attributes prozess */
	short getProzess();

	/** dient zum Lesen (über Referenzübergabe) der entsprechenden privaten Attribute. */
	void getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor);

	/** Diese Methode dient zum Schreiben des privaten Attributes spannung */
	void setSpannung (double spannung);

	/** Diese Methode dient zum Schreiben des privaten Attributes temp */
	void setTemp( double temp);

	/** Diese Methode dient zum Schreiben des privaten Attributes prozess */
	void setProzess (short prozess);

	/** Gibt alle berechneten Faktoren auf dem Bildschirm aus. */
	void ausgabeFaktoren();

};


#endif // _Faktoren_
