/**
Menue Klasse
zuständig für Ein/Ausgabe und Navigation durch das Programm

Eine Menüführung innerhalb der Konsole lässt sich am einfachsten realisieren, indem man zunächst den
Inhalt der Konsole löscht, die Bildschirmausgabe aktualisiert und dann die Auswahlmöglichkeiten über
eine einfache case-Struktur abfragt.
Für die Umsetzung unter Visual Studio können die folgenden Befehle hilfreich sein:
system("pause"); pausiert das Programm bis eine beliebige Taste gedrückt wird.
system("cls"); löscht den Inhalt der Konsole.

Erwünschte Ausgabe:
******************************************
*     IT-Projektpraktikum WS2011/2012    *
*                                        *
* Laufzeitanalyse synchroner Schaltwerke *
******************************************

(1) aeussere Faktoren
Spannung [Volt]: 1.2
Temperatur [Grad Celsius]: 55
Prozess (1=slow, 2=typical, 3=fast): 1

(2) Bibliothek
Pfad zur Bibliotheksdatei: c:\bib.txt

(3) Schaltwerk
Pfad zur Schaltwerksdatei: c:\csd.txt

(4) Analyse starten

(5) Programm beenden

Waehle einen Menuepunkt und bestaetige mit Enter:
*/


#include "Menue.h"

Menue::Menue()
{
/**
ist der Konstruktor der Klasse. Erzeugt die Objekte meineFaktoren, meineBibliothek,
meinSignalListeErzeuger, meinGraphErzeuger und meinLaufzeitAnalysator.
*/

/*Faktoren meineFaktoren = new Faktoren();
Bibliothek meineBibliothek = new Bibliothek;
SignalListeErzeuger meinSignalListeErzeuger = new SignalListeErzeuger;
GraphErzeuger meinGraphErzeuger = new GraphErzeuger;
LaufzeitAnalysator meinLaufzeitAnalysator = new LaufzeitAnalysator;
Signal* signale = new Signal;*/
}

Menue::~Menue()
{
/**
ist der Destruktor der Klasse.
*/
}

void Menue::start(){
/**
schreibt das Hauptmenü in die Konsole und startet die Hauptschleife, in der durch das Hauptmenü
navigiert wird.
*/
    cout << " ****************************************** \n *     IT-Projektpraktikum WS2011/2012    * \n *                                        * \n * Laufzeitanalyse synchroner Schaltwerke * \n ******************************************" << endl; //Ausgabe des "Headers"
}

void Menue::faktorenMenue(){
/**
Im Untermenü der äußeren Faktoren sollen die Außenbedingungen geändert und die daraus resultie-
renden Faktoren ausgegeben werden können. Dazu wird von der Klasse Faktoren eine Ausgabeme-
thode bereitgestellt.
*/
}

void Menue::bibliothekMenue(){
/**
 Im Untermenü der Bibliothek soll der Pfad zur Bibliotheksdatei geändert werden können und man
soll sich zur Kontrolle auch die Datei im Menü anzeigen lassen können. Auch die Klasse Bibliothek
stellt dazu eine Ausgabemethode bereit.
*/
}

void Menue::schaltwerkMenue(){
/**
Im Untermenü des Schaltwerks soll der Pfad zur Schaltwerksdatei veränderbar sein. Zur Kon-
trolle soll diese ausgegeben werden können. Außerdem soll eine Liste der Signale und die Gra-
phstruktur ausgegeben werden können. Zu diesen Ausgaben werden Methoden durch die Klassen
SignalListeErzeuger und LaufzeitAnalysator bereitgestellt.
*/
}

void Menue::analyse(){
/**
ruft die zur Analyse benötigten Methoden auf und gibt das Ergebnis auf dem Bildschirm aus.
*/
}

void Menue::menueKopf(){
/**
Gibt den Kopf der Menüs aus. Dieser bleibt in Hauptmenü und allen Untermenüs gleich.
*/
}
