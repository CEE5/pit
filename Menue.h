#ifndef MENUE_H
#define MENUE_H
#include "SignalListeErzeuger.h"
#include <iostream>
#include <string>
#include "Faktoren.h"
#include "Bibliothek.h"
#include "cross-compatibility.h"
#include "GraphErzeuger.h"
#include "LaufzeitAnalysator.h"

using namespace std;

class Menue
{
    public:
        Menue();

        virtual ~Menue();

        void start();

    protected:


    private:

        Faktoren meineFaktoren;
        Bibliothek meineBibliothek;
        SignalListeErzeuger meinSignalListeErzeuger;

        GraphErzeuger meinGraphErzeuger;

        //LaufzeitAnalysator meinLaufzeitAnalysator;

       // Signal* signale;



        void faktorenMenue();

        void bibliothekMenue();

        void schaltwerkMenue();

        void analyse();

        void menueKopf();

        string input;

};

#endif // MENUE_H
