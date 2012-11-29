#include "SignalListeErzeuger.h"

SignalListeErzeuger::SignalListeErzeuger()
{
    //ctor
    anzahlSignale = 0;
    frequenz = 0;
    /*setDatei(file);
    readFile();*/ ///Manuell im Menü aufrufen
}
SignalListeErzeuger::~SignalListeErzeuger()
{
    //dtor
}

Signal* SignalListeErzeuger::getSignal(int i) {
    return &signale.at(i) ;
}

int SignalListeErzeuger::readFile() {
    signale.clear();
    string line;
    ifstream listfile(getDatei().data());
    Signal* bufferobj = new Signal;
    signale.push_back( *bufferobj );
    if (listfile.is_open()) {
        cout << "INFO: file is open" << endl;
        while (!listfile.eof()) {
            getline(listfile,line);
            if (((line.substr(0,2)) == "//") or (line == "\r") or (line == "")) {
                cout << "INFO: drop, comment or empty line" << endl;
            }else if ((line.substr(0,12)) == "ARCHITECTURE") {
                cout << "INFO: drop, ARCHITECTURE shit" << endl;
            }else if ((line.substr(0,6)) == "ENTITY") {
                while (1) {
                    getline(listfile,line);
                    if ((line.substr(0,2)) == "//") {
                        cout << "INFO: drop, comment or empty line" << endl;
                    }else if ((line.substr(0,5)) == "INPUT") {
                        cout << "INFO: Found INPUT line!" << endl;
                        readSignalLine(eingang,5,line);
                    }else if ((line.substr(0,6)) == "OUTPUT") {
                        cout << "INFO: Found OUTPUT line!" << endl;
                        readSignalLine(ausgang,6,line);
                    }else if ((line.substr(0,7)) == "SIGNALS") {
                        cout << "INFO: Found SIGNALS line!" << endl;
                        readSignalLine(intern,7,line);
                    }else if ((line.substr(0,5)) == "CLOCK") {
                        cout << "INFO: Found CLOCK line!" << endl;
                        string hr_frequency = line.substr(11,(line.length()-11));                    ///Schneide Frequenz aus
                        frequenz = atoi(hr_frequency.data());                                        ///Lese Frequenzzahl
                        if (hr_frequency.substr(hr_frequency.size()-5,1)=="M") {                                                ///Multipliziere frequenz
                            frequenz = frequenz * 1000000;
                        } else if (hr_frequency.substr(hr_frequency.size()-5,1)=="k") {
                            frequenz = frequenz * 1000;
                        }
                        bufferobj->setSignalTyp(clk);
                        signale.at(0) = *bufferobj;
                        cout << "INFO: Set clk to:  " << frequenz << endl;
                    }else if (line == "\r" or (line == "")){
                        cout << "INFO: Found empty line, leave ENTITY area!" << endl;
                        break;
                    }else {
                        cout << "ERR: Error reading line" << endl;
                        break;
                    }
                }
            }else if ((line.substr(0,5)) == "BEGIN") {
                while (1) {
                    getline(listfile,line);
                    if ((line.substr(0,2)) == "//") {
                        cout << "comment" << endl;
                    }else if ((line.substr(0,1)) == "g") {
                        cout << "INFO: Found GATE line!" << endl;
                        if (readGateLine(line) == 1 ) {                                          ///Wenn Kurzschluss bereits vorhanden
                            cout << "ERR: Short curcuit" << endl;
                            return 1;
                        }
                    }else if ((line.substr(0,6)) == "END") {
                        cout << "INFO: Found END line!" << endl;
                            signalTypen tmpsig;
                            tmpsig = signale.at(0).getSignalTyp();
                            cout << "DEBUG "<< tmpsig << endl;
                            setAnzahlSignale(signale.size());                                       ///AnzahlSignale auf die Größe des Vektor setzen
                            cout << "DEBUG: AnzahlSignale: " << getAnzahlSignale() << endl;
                        return 0;
                    }else {
                        cout << "ERR: Error reading line" << endl;
                        break;
                    }
                }
            } else {//------------------------------------------else
                cout << "ERR: Error reading headline" << endl;
                break;
            }
        }
    } else {
        cout << "ERR: Error opening file!" << endl;
        return 1;
    }
    return 0;
}

int SignalListeErzeuger::readSignalLine(signalTypen typ, int lengthBegin, string tmpLine) {
    string tmpSignal;
    stringstream tmpStream(tmpLine.substr(lengthBegin+1,(tmpLine.length()-(lengthBegin+2))));       ///Erstellt Stream und schneidet Anfang und Ende ab     //!!!!! noch 1 dazu addieren bei lenghtbegin fuer linux
    while (getline(tmpStream,tmpSignal,',')) {                                                      ///Trennt nach Komma
        cout << "INFO: Aktuelles Signal: " << tmpSignal << endl;
        unsigned int tmpSignalNo = atoi(tmpSignal.substr(1,3).c_str());                                       ///Lese Nummer von aktuellem Signal
        //cout << "DEBUG: tmpSignalNo: " << tmpSignalNo << endl;
        Signal* nullObj = new Signal;                                                                  ///Erzeuge leeres Objekt
        while (signale.size() <= tmpSignalNo) {                                              ///Solange der Vektor kleiner ist als aktuelle Signalnummer
            signale.push_back( *nullObj );                                                             ///Vergrößere Vektor
        }
        signale.at(tmpSignalNo).setSignalTyp(typ);                                          ///Schreibe Typ an Stelle der akt. Signalnummer in Vektor
    }
}

int SignalListeErzeuger::readGateLine(string tmpLine) {
    string gateNo, gatetype, tmpSignal;
    gateNo = tmpLine.substr(0,4);                                       ///Schneide Gatenummer heraus
    gatetype = tmpLine.substr(5,tmpLine.find("(")-5);                   ///Schneide Gatetyp abhängig von der Länge heraus
    tmpLine = tmpLine.substr(tmpLine.find("(")+1,tmpLine.size()-tmpLine.find("(")-3);           ///Schneide Signale heraus   //  !!! ,tmpLine.size()-tmpLine.find("(")-3);   orig -4
    string tmpOut = (tmpLine.substr(tmpLine.size()-2,3));                                       ///Schneide Ausgang heraus      // !!!! Line.size()-2,3)); orig -3
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
        //cout << "tmpSignal: " << tmpSignal << endl;
        //cout << "DEBUG: Vect: " << tmpSignal.substr(1,3) << endl;
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
