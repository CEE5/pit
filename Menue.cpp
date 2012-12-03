#include "Menue.h"



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



Menue::Menue()
{
    /**
    ist der Konstruktor der Klasse. Erzeugt die Objekte meineFaktoren, meineBibliothek,
    meinSignalListeErzeuger, meinGraphErzeuger und meinLaufzeitAnalysator.
    */
    Faktoren meineFaktoren;
    Bibliothek meineBibliothek;
    SignalListeErzeuger meinSignalListeErzeuger;



 //   GraphErzeuger meinGraphErzeuger = new GraphErzeuger;
//    LaufzeitAnalysator meinLaufzeitAnalysator = new LaufzeitAnalysator;
 //   Signal* signale = new Signal;
}

Menue::~Menue()
{
    /**
    ist der Destruktor der Klasse.
    */
}

void Menue::start()
{
    /**
    schreibt das Hauptmenü in die Konsole und startet die Hauptschleife, in der durch das Hauptmenü
    navigiert wird.
    */

    while(input != "5") {
        menueKopf();

        /// Faktoren Hauptmenüpunkt
        cout << "(1) aeussere Faktoren \nSpannung [Volt]: " << meineFaktoren.getSpannung() << endl;
        cout << "Temperatur [Grad Celsius]: " << meineFaktoren.getTemp() << endl;
        cout << "Prozess (1=slow, 2=typical, 3=fast): " << meineFaktoren.getProzess() << endl;

        cout << endl;

        /// Bibliothek Hauptmenüpunkt
        cout << "(2) Bibliothek" << endl;
        cout << "Pfad zur Bibliotheksdatei:" << meineBibliothek.getPfad() << endl;

        cout << endl;

        /// Schaltwerk Hauptmenüpunkt
        cout << "(3) Schaltwerk \nPfad zur Schaltwerksdatei: " << meinSignalListeErzeuger.getDatei() << endl;

        cout << "\n(4) Analyse starten \n\n(5) Programm beenden\n\nWaehle einen Menuepunkt und bestaetige mit Enter: ";


        getline(cin, input);
        switch (atoi(input.c_str()))
        {
        case 1:
            faktorenMenue();
            break;
        case 2:
            bibliothekMenue();
            break;
        case 3:
            schaltwerkMenue();
            break;
        case 4:
            analyse();
            break;
        }
    }
}

void Menue::faktorenMenue()
{
    /**
    Im Untermenü der äußeren Faktoren sollen die Außenbedingungen geändert und die daraus resultie-
    renden Faktoren ausgegeben werden können. Dazu wird von der Klasse Faktoren eine Ausgabeme-
    thode bereitgestellt.
    */
    while(input != "5") {
        menueKopf();
       cout << "Untermenue Aeussere Faktoren" << endl;
       cout << "(1) Spannung [Volt]: 1.2" << endl;
       cout << "(2) Temperatur [Grad Celsius]: 55" << endl;
       cout << "(3) Prozess (1=slow, 2=typical, 3=fast): 1" << endl;
       cout << "(4) Ausgabe errechneter Faktoren" << endl;
       cout << "(5) Hauptmenue" << endl << endl;
       cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";

        getline(cin, input);
        switch (atoi(input.c_str())) {
        case 1:
            break;
        }
    }
    input.clear();
}

void Menue::bibliothekMenue()
{
    /**
     Im Untermenü der Bibliothek soll der Pfad zur Bibliotheksdatei geändert werden können und man
    soll sich zur Kontrolle auch die Datei im Menü anzeigen lassen können. Auch die Klasse Bibliothek
    stellt dazu eine Ausgabemethode bereit.
    */

    string pf;
    while(input != "3") {
        menueKopf();
        cout << "Untermenue Bibliothek" <<endl;
        cout << "(1) Pfad zur Bibliotheksdatei: " << meineBibliothek.getPfad() <<endl;
        cout << "(2) Ausgabe der Bibliotheksdatei" << endl;
        cout << "(3) Hauptmenue" << endl<< endl;
        cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";

        getline(cin, input);
        switch (atoi(input.c_str())) {
        case 1:
            cout <<"Pfad eingeben: ";
            cin >> pf;
            if(!meineBibliothek.pfadEinlesen(pf)){
                cout << "Fehler beim einlesen!" << endl;
                cin.get();
            }
            break;
        case 2:
            meineBibliothek.dateiAusgabe();
            cin.get();
            break;
        }
    }
    input.clear();
}

void Menue::schaltwerkMenue()
{
    /**
    Im Untermenü des Schaltwerks soll der Pfad zur Schaltwerksdatei veränderbar sein. Zur Kon-
    trolle soll diese ausgegeben werden können. Außerdem soll eine Liste der Signale und die Gra-
    phstruktur ausgegeben werden können. Zu diesen Ausgaben werden Methoden durch die Klassen
    SignalListeErzeuger und LaufzeitAnalysator bereitgestellt.
    */
    while(input != "5") {
        string pf;
        menueKopf();
        cout << "Untermenue Schaltwerk" << endl;
        cout << "(1) Pfad zur Schaltnetzdatei: " << meinSignalListeErzeuger.getDatei() << endl;
        cout << "(2) Ausgabe der Schaltnetzdatei" << endl;
        cout << "(3) Ausgabe der Signale" << endl;
        cout << "(4) Ausgabe der Graphstruktur" << endl;
        cout << "(5) Hauptmenue\n\nWaehle einen Menuepunkt und bestaetige mit Enter: ";

        getline(cin, input);
        switch (atoi(input.c_str())) {
        case 1:
            cout << "Pfad eingeben: ";
            cin >>pf;
            meinSignalListeErzeuger.setDatei(pf);
            meinSignalListeErzeuger.readFile();
            cin.ignore();
            cin.get();
            break;
        case 2:
            cout << "Ausgabe der \"puren\" Datei..." << endl;
            break;
        case 3:
            cout << "Vector size: " << meinSignalListeErzeuger.getAnzahlSignale() << endl;
            cout << "Vectorcontent:"  << endl;
            for (int i=0;i<meinSignalListeErzeuger.getAnzahlSignale();i++) {
                cout << "---------------------------------------------\n";
                cout << "Nummer: " << i << endl;
                cout << "Signaltyp: " << meinSignalListeErzeuger.getSignal(i)->getSignalTyp() << endl;
                cout << "Quelle: " << meinSignalListeErzeuger.getSignal(i)->getQuelle() << endl;
                cout << "Quellentyp: " << meinSignalListeErzeuger.getSignal(i)->getQuellenTyp() << endl;
                cout << "Anzahlziele: " << meinSignalListeErzeuger.getSignal(i)->getAnzahlZiele() << endl;
                for (int i1=0;i1<meinSignalListeErzeuger.getSignal(i)->getAnzahlZiele();i1++) {
                    cout << "-----" << meinSignalListeErzeuger.getSignal(i)->getZiel(i1) <<endl;
                }
            }
            cin.get();
            break;
        case 4:
            cout << "Ausgabe der Graphstruktur" << endl;

            //test grapherzeuger

            GraphErzeuger gez;
            cout << "INFO: set biblio"<<endl;
            gez.setBibliothek(meineBibliothek);
            cout << "INFO: erzeuge liste.."<<endl;
            gez.listeAnlegen(meinSignalListeErzeuger);
            cout << "INFO: liste erzeugt"<<endl;
            cout<< "INFO: graph erzeugen:\n "<<endl;
            cin.get();
            gez.graphErzeugen(meinSignalListeErzeuger);

            cin.get();
            gez.listenAusgabe( );
            cin.get();

            //

            break;
        }
    }
    input.clear();
}

void Menue::analyse()
{
    /**
    ruft die zur Analyse benötigten Methoden auf und gibt das Ergebnis auf dem Bildschirm aus.
    */
    while(input != "5") {
        menueKopf();

        getline(cin, input);
        switch (atoi(input.c_str())) {
        case 1:
            break;
        }
    }
    input.clear();
}

void Menue::menueKopf()
{
    /**
    Gibt den Kopf der Menüs aus. Dieser bleibt in Hauptmenü und allen Untermenüs gleich.
    */
    clear_screen();
    cout << " ****************************************** \n *     IT-Projektpraktikum WS2011/2012    * \n *                                        * \n * Laufzeitanalyse synchroner Schaltwerke * \n ******************************************" << endl << endl; //Ausgabe des "Headers"
}
