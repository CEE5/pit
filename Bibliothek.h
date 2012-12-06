#ifndef BIBLIOTHEK_H
#define BIBLIOTHEK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "cross-compatibility.h"


#include "GatterTyp.h"
#include "Flipflop.h"


using namespace std;

class Bibliothek{
public:
    Bibliothek();
    virtual ~Bibliothek();

    string getPfad(void);
    GatterTyp* getBibElement(string typ);
    void dateiAusgabe(void);
    void dateiAuswerten(void);
    bool pfadEinlesen(string pfad);

protected:
private:
    string datei;
    vector<GatterTyp> bibElemente;
    vector<Flipflop> bibHilfe;

    void openError(void);
    void readError(void);
};

#endif // BIBLIOTHEK_H
