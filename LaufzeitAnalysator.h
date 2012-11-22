// LaufzeitAnalysator.h
//
//


#ifndef _LAUFZEITANALYSATOR_
#define _LAUFZEITANALYSATOR_

#include <map>

class LaufzeitAnalysator {
  private:

  Faktoren* faktoren;
  long frequenz,
  string uebergangspfad;
  string ausgangspfad;
  double laufzeitUebergangspfad;
  double laufzeitAusgangspfad;
  struct{SchaltwerkElement* VaterElement; double PfadLaufzeit} DFS_Daten;
  map< SchaltwerkElement* , DFS_Daten > DFS_Zwischenspeicher;

  public:


};


#endif // _LAUFZEITANALYSATOR_
