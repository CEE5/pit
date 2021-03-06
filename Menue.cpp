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
*     IT-Projektpraktikum WS2012/2013    *
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
    Im Untermenü der äusseren Faktoren sollen die Aussenbedingungen geändert und die daraus resultie-
    renden Faktoren ausgegeben werden können. Dazu wird von der Klasse Faktoren eine Ausgabeme-
    thode bereitgestellt.
    */
    while(input != "5") {
        menueKopf();
        cout << "Untermenue Aeussere Faktoren" << endl;
        cout << "(1) Spannung [Volt]: " << meineFaktoren.getSpannung() << endl;
        cout << "(2) Temperatur [Grad Celsius]: " << meineFaktoren.getTemp() << endl;
        cout << "(3) Prozess (1=slow, 2=typical, 3=fast): " << meineFaktoren.getProzess() << endl;
        cout << "(4) Ausgabe errechneter Faktoren" << endl;
        cout << "(5) Hauptmenue" << endl << endl;
        cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";

        getline(cin, input);
        switch (atoi(input.c_str())) {
        case 1:
            cout << "Neue Spannung eingeben: ";
            getline(cin, input);
            	if  ( (atof(input.c_str()) >= 1.08) && (atof(input.c_str()) <= 1.32) ) {
                    meineFaktoren.setSpannung(atof(input.c_str()));
            	} else {
                    cout << "Die Spannung muss zwischen 1.08 und 1.32 liegen" <<endl;
                    cin.get();
            	}
            break;
        case 2:
            cout << "Neue Temperatur eingeben: ";
            getline(cin, input);
            if  ( (atof(input.c_str()) >= -25) && (atof(input.c_str()) <= 125)) {
                meineFaktoren.setTemp(atof(input.c_str()));
            } else {
                cout << "Die Temperatur muss zwischen -25 und 125 liegen!";
                cin.get();
            }
            break;
        case 3:
            cout << "Neue Prozess Geschwindigkeit eingeben: ";
            getline(cin, input);
            if((atoi(input.c_str())<=3) & (atoi(input.c_str()) >= 1)) {
                meineFaktoren.setProzess(atoi(input.c_str()));
            } else {
                cout << "Es gibt nur 1, 2 und 3!" <<endl;
                cin.get();
            }
            break;
        case 4:
            meineFaktoren.ausgabeFaktoren();
            cin.get();
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
            } else {
                meineBibliothek.dateiAuswerten();
                meinGraphErzeuger.setBibliothek(&meineBibliothek);
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
    trolle soll diese ausgegeben werden können. Ausserdem soll eine Liste der Signale und die Gra-
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
            if (meineBibliothek.getPfad() != "") {
                cout << "Pfad eingeben: ";
                cin >>pf;
                ifstream f(pf.c_str());
                if(!f.good()) {
                    cout << "Datei nicht gefunden!"<<endl;
                    cin.ignore();
                    cin.get();
                } else {

                    meinSignalListeErzeuger.setDatei(pf);
                    if (meinSignalListeErzeuger.readFile() == 21 ) {
                        //cout << "Kurzschluss gefunden!"<< endl;
                        cin.get();
                    } else {

                        debug_pause();
                        meinGraphErzeuger.listeAnlegen(meinSignalListeErzeuger);
                        meinGraphErzeuger.graphErzeugen(meinSignalListeErzeuger);
                    }
                    debug_pause();
                }
            } else {
                cout << "\n Die Bibliothek muss als erstes geladen werden!";
                cin.get();
            }
            break;
        case 2:
            meinSignalListeErzeuger.dateiAusgabe();
            cin.get();
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
            meinGraphErzeuger.listenAusgabe( );
            cin.get();
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
    if ((meineFaktoren.getTemp() != 0) && (meineFaktoren.getSpannung() != 0) && (meineFaktoren.getProzess() != 0) && (meineBibliothek.getPfad() != "") && (meinSignalListeErzeuger.getDatei() != "") ) {
        LaufzeitAnalysator lza( &meinGraphErzeuger, &meineFaktoren);
        lza.berechne_LaufzeitEinzelgatter();

        if(lza.DFS_startSuche(&meinGraphErzeuger)){

            lza.maxFrequenz(meinSignalListeErzeuger.getFrequenz());
        }
    } else {
        cout << "Es sind noch nicht alle benötigten Parameter ausgefüllt!";
    }
    cin.get();
    input.clear();
}

void Menue::menueKopf()
{
    /**
    Gibt den Kopf der Menüs aus. Dieser bleibt in Hauptmenü und allen Untermenüs gleich.
    */
    clear_screen();
    cout << " ****************************************** \n *     IT-Projektpraktikum WS2012/2013    * \n *                                        * \n * Laufzeitanalyse synchroner Schaltwerke * \n ******************************************" << endl << endl; //Ausgabe des "Headers"
}
