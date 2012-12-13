#include "LaufzeitAnalysator.h"


LaufzeitAnalysator::LaufzeitAnalysator(GraphErzeuger* g, Faktoren* f)
{

    faktoren = f;
    gE = g;

     signallaufzeit* = new double[gE->getGatterAnzahl()];
}

LaufzeitAnalysator::~LaufzeitAnalysator()
{
    //dtor
}

void LaufzeitAnalysator::DFS(ListenElement* s){
    for (ListenElement* ptr = gE->getStartElement(); ptr != NULL; ptr = ptr->getNextElement()){


    }


}
void LaufzeitAnalysator::DFS_Visit(ListenElement* k,ListenElement* s){

}
