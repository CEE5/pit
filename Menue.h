#ifndef MENUE_H
#define MENUE_H

#include <iostream>
using namespace std;

class Menue
{
    public:
        Menue();

        virtual ~Menue();

        void start();

    protected:


    private:

        /*Faktoren meineFaktoren;
        Bibliothek meineBibliothek;
        SignalListeErzeuger meinSignalListeErzeuger;
        GraphErzeuger meinGraphErzeuger;
        LaufzeitAnalysator meinLaufzeitAnalysator;
        Signal* signale;*/

        void faktorenMenue();

        void bibliothekMenue();

        void schaltwerkMenue();

        void analyse();

        void menueKopf();


};

#endif // MENUE_H
