#ifndef BIBLIOTHEK_H
#define BIBLIOTHEK_H


#include <string>
#include <vector>
using namespace std;

class Bibliothek
{
public:
    Bibliothek();
    virtual ~Bibliothek();

    string getPfad(void);
//    GatterTyp getBibElement(string);
    void dateiAusgabe(void);
    void dateiAuswerten(void);
    void pfadEinlesen(void);

protected:
private:
    string datei;
//  vector<GatterTyp*> bibElemente;

    void openError(void);
    void readError(void);
};

#endif // BIBLIOTHEK_H
