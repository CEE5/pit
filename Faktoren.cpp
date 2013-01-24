// Faktoren.cpp
//
#include "Faktoren.h"
#include <iostream>

using namespace std;


/** Konstruktor der Klasse. Er soll beim Anlegen der Klasse alle Attribute mit dem Wert 0 initialisieren.*/
Faktoren::Faktoren(){
	spannung = 0;
	temp = 0;
	prozess = 0;
	spannungFaktor = 0;
	tempFaktor = 0;
	prozessFaktor = 0;
}


/** Destruktor der Klasse.*/
Faktoren::~Faktoren(){}

/** Gibt alle berechneten Faktoren auf dem Bildschirm aus. */
void Faktoren::ausgabeFaktoren(){
	cout << endl << "Spannungsfaktor: \t" << spannungFaktor <<
			endl << "Temperaturfaktor: \t" << tempFaktor << endl <<
					"Prozessfaktor: \t\t" << prozessFaktor << endl;
}


/** dient zum Lesen (über Referenzübergabe) der entsprechenden privaten Attribute. */						//kuriose (unfertige?) Funktion
void Faktoren::getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor){
	//
	//erst spaeter??
	//keine Ahnung, ob das so gemeint ist

	spgFaktor = spannungFaktor;
	tmpFaktor = tempFaktor;
	przFaktor = prozessFaktor;
}


/** Beinhaltet die Werte Spannungstabelle in Form eines 2-dimensionalen Arrays. überprüft anhand des Arrays, ob der Wert vom Attribut spannung innerhalb
der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zurück gegeben. Ansonsten wird die private Methode
berechneFaktor() mit dem Wert, dem Array und der Grösse des Arrays als übergabeparameter aufgerufen. Der Rückgabewert der Methode berechneFaktor() wird in dem
Attribut spannungFaktor gespeichert.*/
bool Faktoren::berechneSpannungFaktor (double spannung){
	if  ( (spannung >= 1.08) && (spannung <= 1.32)) {
		double spgTabelle[][2] = {	{1.08 , 1.121557},
									{1.12 , 1.075332},
									{1.16 , 1.035161},
									{1.20 , 1.000000},
									{1.24 , 0.968480},
									{1.28 , 0.940065},
									{1.32 , 0.9144822}};

		spannungFaktor = Faktoren::berechneFaktor(spannung, spgTabelle, 7 );

		return true;
	} else {
		cout << endl << "Fehler: Spannung ueber- oder unterschreitet die Grenzwerte!" << endl ;
		return false;
	}

}


/** Beinhaltet die Werte Temperaturtabelle in Form eines 2-dimensionalen Arrays. überprüft anhand des Arrays, ob der Wert vom Attribut temp innerhalb
der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zurück gegeben. Ansonsten wird die private Methode
berechneFaktor() mit dem Wert, dem Array und der Grösse des Arrays als übergabeparameter aufgerufen. Der Rückgabewert der Methode berechneFaktor() wird in dem
Attribut tempFaktor gespeichert. */
bool Faktoren::berechneTempFaktor (double temp){
	if  ( (temp >= -25) && (temp <= 125)) {
		double tempTabelle[][2] = {	{-25 , 0.897498},
									{-15 , 0.917532},
									{  0 , 0.948338},
									{ 15 , 0.979213},
									{ 25 , 1.000000},
									{ 35 , 1.020305},
									{ 45 , 1.040540},
									{ 55 , 1.061831},
									{ 65 , 1.082983},
									{ 75 , 1.103817},
									{ 85 , 1.124124},
									{ 95 , 1.144245},
									{ 105 , 1.164563},
									{ 115 , 1.184370},
									{ 125 , 1.204966}};

		tempFaktor = Faktoren::berechneFaktor(temp, tempTabelle, 15 );

		return true;
	} else {
		cout << endl << "Fehler: Temperatur ueber- oder unterschreitet die Grenzwerte!" << endl ;
		return false;
	}

}



/** Beinhaltet die Werte Prozesstablle in Form eines 2-dimensionalen Arrays. überprüft anhand des Arrays, ob der Wert vom Attribut prozess innerhalb
der vorgegebenen Grenzen liegt. Wenn dies nicht der Fall ist, wird eine Fehlermeldung ausgegeben und false zurück gegeben. Ansonsten wird die private Methode
berechneFaktor() mit dem Wert, dem Array und der Grösse des Arrays als übergabeparameter aufgerufen. Der Rückgabewert der Methode berechneFaktor() wird in dem
Attribut prozessFaktor gespeichert.*/
bool Faktoren::berechneProzessFaktor (short prozess){
	if  ((prozess >= 1) && (prozess <= 3)) {
		double przTabelle[][2] = {	{ 1 , 1.174235},  /**  1 = slow    */
									{ 2 , 1.000000},  /**  2 = typical */
									{ 3 , 0.876148}}; /**  3 = fast    */

		prozessFaktor = Faktoren::berechneFaktor(prozess, przTabelle, 3 );

		return true;
	} else {
		cout << endl << "Fehler: Prozess "<< prozess <<" existiert nicht !! [Slow->1, Typical->2, Fast->3]" << endl ;
		return false;
	}

}


/** Die Methode durchsucht das übergebene Array nach dem übergebenen Wert. Wenn der Wert im Array vorhanden ist (1. Spalte der Tabelle) wird der zugehörige
Faktor (2. Spalte der Tabelle) direkt zurückgegeben, ansonsten wird mit den am nächsten liegenden Punkten eine Interpolation über die entsprechende Methode
gestartet und der interpolierte Wert zurückgegeben. */
double Faktoren::berechneFaktor (double wert, double arr[][2], int laenge){

	double Faktor;
	double vgl = 0;
	double untereSchranke[2] = { (arr[0][0]) , (arr[0][1]) };
	double obereSchranke[2] = { (arr[laenge-1][0]) , (arr[laenge-1][1]) };

	for (int i=0; i < laenge; i++){
		if (wert > arr[i][0]){
			untereSchranke[0] = arr[i][0];
			untereSchranke[1] = arr[i][1];
			obereSchranke[0] = arr[i+1][0];
			obereSchranke[1] = arr[i+1][1];
		}
		else if (wert == arr[i][0]){
			vgl = arr[i][0];
			Faktor = arr[i][1];
		}
	}

	if (wert != vgl){
		Faktor = Faktoren::interpolation ( wert, untereSchranke[0], obereSchranke[0], untereSchranke[1], obereSchranke[1]);
	}
	/** cout <<untereSchranke[0]<<endl<< obereSchranke[0]<< endl<<untereSchranke[1]<<endl<< obereSchranke[1] <<endl; //zum testen */
	return Faktor;
}


/** Diese Methode interpoliert einen Wert zwischen zwei vorgegebenen Punkten im 2D-Raum. Dabei bestimmen x1,
y1 und x2, y2 jeweils die Koordinaten der zwei Punkte zwischen denen interpoliert werden soll. Der
übergabeparameter wert bestimmt den x-Wert des gesuchten Wertes, dabei gilt x1 < wert < x2.*/
double Faktoren::interpolation ( double wert, double x1, double x2, double y1, double y2){
	//
	double interpolwert = wert * (y2-y1)/(x2-x1) + (y1 - (y2-y1)/(x2-x1)*x1);
	return interpolwert;
}


/** Diese Methode dient zum Lesen des privaten Attributes spannung */
double Faktoren::getSpannung(){
	return spannung;
}


/** Diese Methode dient zum Lesen des privaten Attributes temp (die
eratur) */
double Faktoren::getTemp(){
	return temp;
}


/** Diese Methode dient zum Lesen des privaten Attributes prozess */
short Faktoren::getProzess(){
	return prozess;
}


/** Diese Methode dient zum Schreiben des privaten Attributes spannung */
void Faktoren::setSpannung (double spannung){
	 this->spannung = spannung;
	 berechneSpannungFaktor(spannung);
}


 /** Diese Methode dient zum Schreiben des privaten Attributes temp */
void Faktoren::setTemp( double temp){
	this->temp = temp;
	berechneTempFaktor(temp);
}


/** Diese Methode dient zum Schreiben des privaten Attributes prozess */
void Faktoren::setProzess (short prozess){
	this->prozess = prozess;
	berechneProzessFaktor(prozess);
}
