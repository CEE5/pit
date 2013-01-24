#include "SignalListeErzeuger.h"

/**Konstruktor
Setzt alle Variablen auf 0
**/
SignalListeErzeuger::SignalListeErzeuger()
{
    //ctor
    anzahlSignale = 0;
    frequenz = 0;
    datei="";
    /*setDatei(file);
    readFile();*/ ///Manuell im Menü aufrufen
}

/**Destruktor
**/
SignalListeErzeuger::~SignalListeErzeuger()
{
    //dtor
}

/**dateiAusgabe
öffnet die Datei die in der 'datei' Variable der Klasse gespeichert ist und gibt die aus
**/
void SignalListeErzeuger::dateiAusgabe(void)
{
    ifstream f(datei.c_str());

    string buffer;

    int i=0;

    if(f.good())
    {
        while (!f.eof())
        {
            getline(f,buffer);
            cout << i<<": "<<buffer << endl;
            i++;
        }
    }
    else
    {
        cout << "ERR: Can not read file!";
    }

}
/** Gibt Signal aus dem 'signale' Vektor an der im Parameter spezifizierten Stelle zurück
**/
Signal* SignalListeErzeuger::getSignal(int i) {
    return &signale.at(i) ;
}

/**Liest die 'datei' aus und beginnt mit der Auswertung
**/
int SignalListeErzeuger::readFile() {
    signale.clear();                              ///Vektor 'signale' wird geleert
    string line;
    ifstream listfile(getDatei().data());           ///öffne Dateistream
    Signal* bufferobj = new Signal;
    signale.push_back( *bufferobj );                ///Reserviere leeres Objekt für die CLOCK
    if (listfile.is_open()) {
        //debug_msg( "INFO: file is open" );
        while (!listfile.eof()) {
            getline(listfile,line);                         ///liest Zeile für Zeile aus
            if (((line.substr(0,2)) == "//") or (line == "\r") or (line == "")) {
                debug_msg( "INFO: drop, comment or empty line" );
            }else if ((line.substr(0,12)) == "ARCHITECTURE") {                              ///Wenn Kommentar, leere Zeile oder Schwachsinn drin steht, passiert gar nichts
                debug_msg( "INFO: drop, ARCHITECTURE shit" );
            }else if ((line.substr(0,6)) == "ENTITY") {
                while (1) {
                    getline(listfile,line);
                    if ((line.substr(0,2)) == "//") {
                        debug_msg( "INFO: drop, comment or empty line" );
                    }else if ((line.substr(0,5)) == "INPUT") {
                        debug_msg( "INFO: Found INPUT line!" );
                        readSignalLine(eingang,5,line);
                    }else if ((line.substr(0,6)) == "OUTPUT") {
                        debug_msg( "INFO: Found OUTPUT line!" );
                        readSignalLine(ausgang,6,line);
                    }else if ((line.substr(0,7)) == "SIGNALS") {
                        debug_msg( "INFO: Found SIGNALS line!" );
                        readSignalLine(intern,7,line);
                    }else if ((line.substr(0,5)) == "CLOCK") {
                        debug_msg( "INFO: Found CLOCK line!" );
                        string hr_frequency = line.substr(11,(line.length()-11));                    ///Schneide Frequenz aus
                        frequenz = atoi(hr_frequency.data());                                        ///Lese Frequenzzahl
                        if (hr_frequency.substr(hr_frequency.size()-5,1)=="M") {                                                ///Multipliziere frequenz
                            frequenz = frequenz * 1000000;
                        } else if (hr_frequency.substr(hr_frequency.size()-5,1)=="k") {
                            frequenz = frequenz * 1000;
                        }
                        bufferobj->setSignalTyp(clk);
                        signale.at(0) = *bufferobj;
                        debug_msg( "INFO: Set clk to:  " << frequenz );
                    }else if (line == "\r" or (line == "")){
                        debug_msg( "INFO: Found empty line, leave ENTITY area!" );
                        break;
                    }else {
                        debug_msg( "ERR: Error reading line" );
                        break;
                    }
                }
            }else if ((line.substr(0,5)) == "BEGIN") {
                while (1) {
                    getline(listfile,line);
                    if ((line.substr(0,2)) == "//") {
                        debug_msg( "comment" );
                    }else if ((line.substr(0,1)) == "g") {
                        debug_msg( "INFO: Found GATE line!" );
                        if (readGateLine(line) == 1 ) {                                          ///Wenn Kurzschluss bereits vorhanden
                            cout << "ERR: Short curcuit"  << endl;
                            cin.get();
                            return 21;
                        }
                    }else if ((line.substr(0,6)) == "END") {
                        debug_msg( "INFO: Found END line!" );
                            signalTypen tmpsig;
                            tmpsig = signale.at(0).getSignalTyp();
                            debug_msg( "DEBUG "<< tmpsig );
                            setAnzahlSignale(signale.size());                                       ///AnzahlSignale auf die Grösse des Vektor setzen
                            debug_msg( "DEBUG: AnzahlSignale: " << getAnzahlSignale() );
                        return 0;
                    }else {
                        debug_msg( "ERR: Error reading line" );
                        break;
                    }
                }
            } else {//------------------------------------------else
                debug_msg( "ERR: Error reading headline" );
                break;
            }
        }
    } else {
        cout << "ERR: Error opening file!";
        cin.get();
        return 1;
    }
    return 0;
}

int SignalListeErzeuger::readSignalLine(signalTypen typ, int lengthBegin, string tmpLine) {
    string tmpSignal;
    stringstream tmpStream(tmpLine.substr(lengthBegin+1,(tmpLine.length()-(lengthBegin+2+linuxzusatz))));       ///Erstellt Stream und schneidet Anfang und Ende ab
    while (getline(tmpStream,tmpSignal,',')) {                                                      ///Trennt nach Komma
        debug_msg( "INFO: Aktuelles Signal: " << tmpSignal );
        unsigned int tmpSignalNo = atoi(tmpSignal.substr(1,3).c_str());                                       ///Lese Nummer von aktuellem Signal
        debug_msg( "DEBUG: tmpSignalNo: " << tmpSignalNo );
        Signal* nullObj = new Signal;                                                                  ///Erzeuge leeres Objekt
        while (signale.size() <= tmpSignalNo) {                                              ///Solange der Vektor kleiner ist als aktuelle Signalnummer
            signale.push_back( *nullObj );                                                             ///Vergrössere Vektor
        }
        signale.at(tmpSignalNo).setSignalTyp(typ);                                          ///Schreibe Typ an Stelle der akt. Signalnummer in Vektor
    }
}

int SignalListeErzeuger::readGateLine(string tmpLine) {
    string gateNo, gatetype, tmpSignal;
    gateNo = tmpLine.substr(0,4);                                       ///Schneide Gatenummer heraus
    gatetype = tmpLine.substr(5,tmpLine.find("(")-5);                   ///Schneide Gatetyp abhängig von der Länge heraus
    tmpLine = tmpLine.substr(tmpLine.find("(")+1,tmpLine.size()-tmpLine.find("(")-3-linuxzusatz);           ///Schneide Signale heraus
    string tmpOut = (tmpLine.substr(tmpLine.size()-2-linuxzusatz,3));                                       ///Schneide Ausgang heraus
    if (signale.at(atoi(tmpOut.c_str())).getQuelle().empty()) {                                     ///Prüfe auf Kurzschluss
        signale.at(atoi(tmpOut.c_str())).setQuelle(gateNo);                                         ///Setze Quelle für Ausgangssignal
    }
    else {
        return 1;
    }
    signale.at(atoi(tmpOut.c_str())).setQuellentyp(gatetype);                                         ///Setze Quelletyp für Ausgangssignal
    tmpLine = tmpLine.erase(tmpLine.size()-5,5);                                                      ///Schneide Ausgang ab
    stringstream tmpStream(tmpLine);                                                            ///Erstelle String stream
    while (getline(tmpStream,tmpSignal,',')) {                                                  ///Trenne nach Komma
        debug_msg( "tmpSignal: " << tmpSignal );
        debug_msg( "DEBUG: Vect: " << tmpSignal.substr(1,3) );
        if (tmpSignal == "clk") {
            signale.at(0).zielHinzufuegen(gateNo);
        }
        else {
            signale.at(atoi((tmpSignal.substr(1,3)).c_str())).zielHinzufuegen(gateNo);               ///Füge Ziele zu aktuellem Signal hinzu
        }
    }
    return 0;
}

long SignalListeErzeuger::getFrequenz(){
    return frequenz;
}
string SignalListeErzeuger::getDatei() {
    return datei;
}
short SignalListeErzeuger::getAnzahlSignale(){
    return anzahlSignale;
}
void SignalListeErzeuger::setFrequenz(long freq){
    frequenz = freq;
}
void SignalListeErzeuger::setDatei(string file){
    datei = file;
}
void SignalListeErzeuger::setAnzahlSignale(short nSignals){
    anzahlSignale = nSignals;
}
