#include "SignalListeErzeuger.h"

SignalListeErzeuger::SignalListeErzeuger(string file)
{
    //ctor
    anzahlSignale = 0;
    frequenz = 0;
    setDatei(file);
    readFile();
}
SignalListeErzeuger::~SignalListeErzeuger()
{
    //dtor
}

int SignalListeErzeuger::readFile() {
    string line;
    ifstream listfile(getDatei().data());
    if (listfile.is_open()) {
        cout << "DEBUG: file is open" << endl;
        while (!listfile.eof()) {
            getline(listfile,line);
            if (((line.substr(0,2)) == "//") or (line == "\r")) {
                cout << "DEBUG: drop, comment or empty line" << endl;
            }else if ((line.substr(0,12)) == "ARCHITECTURE") {
                cout << "DEBUG: drop, ARCHITECTURE shit" << endl;
            }else if ((line.substr(0,6)) == "ENTITY") {
                while (1) {
                    getline(listfile,line);
                    if ((line.substr(0,2)) == "//") {
                        cout << "DEBUG: drop, comment or empty line" << endl;
                    }else if ((line.substr(0,5)) == "INPUT") {
                        cout << "DEBUG: Found INPUT line!" << endl;
                        readLine(eingang,5,line);
                    }else if ((line.substr(0,6)) == "OUTPUT") {
                        cout << "DEBUG: Found OUTPUT line!" << endl;
                        readLine(eingang,6,line);
                    }else if ((line.substr(0,7)) == "SIGNALS") {
                        cout << "DEBUG: Found SIGNALS line!" << endl;
                        readLine(eingang,7,line);
                    }else if ((line.substr(0,5)) == "CLOCK") {
                        cout << "DEBUG: Found CLOCK line!" << endl;
                        frequenz = atoi(line.substr(11,(line.length()-11)).data());
                        cout << "DEBUG: Set clk to: " << frequenz << endl;
                    }else if (line == "\r"){
                        cout << "DEBUG: Found empty line, leave ENTITY area!" << endl;
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
                        cout << "DEBUG: Found GATE line!" << endl;
                    }else if ((line.substr(0,6)) == "END") {
                        cout << "DEBUG: Found END line!" << endl;
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

void SignalListeErzeuger::readLine(signalTypen typ, int lengthBegin, string tmpLine) {
    string tmpSignal;
    stringstream tmpStream(tmpLine.substr(lengthBegin+1,(tmpLine.length()-(lengthBegin+3))));
    while (getline(tmpStream,tmpSignal,',')) {
        cout << tmpSignal << endl;
    }
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
void SignalListeErzeuger::setAnzahlSignale(short nSigs){
    anzahlSignale = nSigs;
}
