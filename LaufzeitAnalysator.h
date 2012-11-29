#ifndef _LAUFZEITANALYSATOR_H
#define _LAUFZEITANALYSATOR_H

#include <map>
#include "ListenElement.h"
#include "Faktoren.h"


class LaufzeitAnalysator
{
private:

    Faktoren* faktoren;
    long frequenz;
    string uebergangspfad;
    string ausgangspfad;
    double laufzeitUebergangspfad;
    double laufzeitAusgangspfad;
    struct
    {
        SchaltwerkElement* VaterElement;
        double PfadLaufzeit;
    } DFS_Daten;

    map < SchaltwerkElement* , DFS_Daten > DFS_Zwischenspeicher;



public:
    LaufzeitAnalysator();
    virtual ~LaufzeitAnalysator();
protected:

};

#endif // LAUFZEITANALYSATOR_H
