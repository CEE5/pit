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
                        cout << "comment" << endl;
                    }else if ((line.substr(0,5)) == "INPUT") {
                        cout << "DEBUG: Found INPUT line!" << endl;
                    }else if ((line.substr(0,6)) == "OUTPUT") {
                        cout << "DEBUG: Found OUTPT line!" << endl;
                    }else if ((line.substr(0,7)) == "SIGNALS") {
                        cout << "DEBUG: Found SIGNALS line!" << endl;
                    }else if ((line.substr(0,5)) == "CLOCK") {
                        cout << "DEBUG: Found CLOCK line!" << endl;
                        //frequenz = line.substr(11,(line.length()-11));
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
                        break;
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
