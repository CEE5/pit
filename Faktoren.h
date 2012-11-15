//Faktoren.h
//
//


#ifndef _Faktoren_
#define _Faktoren_

class Faktoren {
//private:
	public:       //zum test, eig private

	double	spannung,
			temp,
			spannungFaktor,
			tempFaktor,
			prozessFaktor;
	short	prozess;

	/** Beinhaltet die Werte Spannungstabelle in Form eines 2-dimensionalen Arrays. �berpr�ft anhand des Arrays, ob der Wert vom Attribut spannung innerhalb
	der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zur�ck gegeben. Ansonsten wird die private Methode
	berechneFaktor() mit dem Wert, dem Array und der Gr��e des Arrays als �bergabeparameter aufgerufen. Der R�ckgabewert der Methode berechneFaktor() wird in dem 
	Attribut spannungFaktor gespeichert.*/
	bool berechneSpannungFaktor (double spannung);

	/** Beinhaltet die Werte Temperaturtabelle in Form eines 2-dimensionalen Arrays. �berpr�ft anhand des Arrays, ob der Wert vom Attribut temp innerhalb
	der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zur�ck gegeben. Ansonsten wird die private Methode
	berechneFaktor() mit dem Wert, dem Array und der Gr��e des Arrays als �bergabeparameter aufgerufen. Der R�ckgabewert der Methode berechneFaktor() wird in dem 
	Attribut tempFaktor gespeichert. */
	bool berechneTempFaktor (double temp);

	/** Beinhaltet die Werte Prozesstablle in Form eines 2-dimensionalen Arrays. �berpr�ft anhand des Arrays, ob der Wert vom Attribut prozess innerhalb
	der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zur�ck gegeben. Ansonsten wird die private Methode
	berechneFaktor() mit dem Wert, dem Array und der Gr��e des Arrays als �bergabeparameter aufgerufen. Der R�ckgabewert der Methode berechneFaktor() wird in dem 
	Attribut prozessFaktor gespeichert.*/
	bool berechneProzessFaktor (short prozess);

	/** Die Methode durchsucht das �bergebene Array nach dem �bergebenen Wert. Wenn der Wert im Array vorhanden ist (1. Spalte der Tabelle) wird der zugeh�rige 
	Faktor (2. Spalte der Tabelle) direkt zur�ckgegeben, ansonsten wird mit den am n�chsten liegenden Punkten eine Interpolation �ber die entsprechende Methode
	gestartet und der interpolierte Wert zur�ckgegeben. */
	double berechneFaktor (double wert, double arr[][2], int laenge);

	/** Diese Methode interpoliert einen Wert zwischen zwei vorgegebenen Punkten im 2D-Raum. Dabei bestimmen x1,
	y1 und x2, y2 jeweils die Koordinaten der zwei Punkte zwischen denen interpoliert werden soll. Der
	�bergabeparameter wert bestimmt den x-Wert des gesuchten Wertes, dabei gilt x1 < wert < x2.*/
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

	/** dient zum Lesen (�ber Referenz�bergabe) der entsprechenden privaten Attribute. */
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