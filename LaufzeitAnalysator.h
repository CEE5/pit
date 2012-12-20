#ifndef _LAUFZEITANALYSATOR_H
#define _LAUFZEITANALYSATOR_H

#include <map>
#include "ListenElement.h"
#include "Faktoren.h"
#include "GraphErzeuger.h"
#include <vector>

    struct DFS_Daten
    {
        SchaltwerkElement* VaterElement;
        double PfadLaufzeit;
    };

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


    void DFS(ListenElement* s);

    map < SchaltwerkElement* , DFS_Daten > DFS_Zwischenspeicher;


    void DFS_Visit(SchaltwerkElement* k, SchaltwerkElement* s);





public:
    LaufzeitAnalysator(GraphErzeuger* gE, Faktoren* f);
    virtual ~LaufzeitAnalysator();

    void berechne_LaufzeitEinzelgatter();

    void DFS_startSuche(GraphErzeuger* ge);

protected:

};

#endif // LAUFZEITANALYSATOR_H
