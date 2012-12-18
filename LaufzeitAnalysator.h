#ifndef _LAUFZEITANALYSATOR_H
#define _LAUFZEITANALYSATOR_H

#include <map>
#include "ListenElement.h"
#include "Faktoren.h"
#include "GraphErzeuger.h"


class LaufzeitAnalysator
{
private:

    Faktoren* faktoren;
    GraphErzeuger* gE;

    long frequenz;
    string uebergangspfad;
    string ausgangspfad;
    double laufzeitUebergangspfad;
    double laufzeitAusgangspfad;

    bool zyklensuche(SchaltwerkElement* se);
    double *signallaufzeit[];
    int *vater[];

    struct DFS_Daten
    {
        SchaltwerkElement* VaterElement;
        double PfadLaufzeit;
    };


    map < SchaltwerkElement* , DFS_Daten > DFS_Zwischenspeicher;

    void DFS(ListenElement* s);
    void DFS_Visit(SchaltwerkElement* k, SchaltwerkElement* s);





public:
    LaufzeitAnalysator(GraphErzeuger* gE, Faktoren* f);
    virtual ~LaufzeitAnalysator();

    void berechne_LaufzeitEinzelgatter();


protected:

};

#endif // LAUFZEITANALYSATOR_H
