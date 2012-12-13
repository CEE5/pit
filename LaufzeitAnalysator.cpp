#include "LaufzeitAnalysator.h"


LaufzeitAnalysator::LaufzeitAnalysator(GraphErzeuger* g, Faktoren* f)
{

    faktoren = f;
    gE = g;

     *signallaufzeit = new double[gE->getGatterAnzahl()];
     *vater = new int [gE->getGatterAnzahl()];

}

LaufzeitAnalysator::~LaufzeitAnalysator()
{
    //dtor
}

void LaufzeitAnalysator::DFS(ListenElement* s){
    int h=0;

    for (ListenElement* ptr = gE->getStartElement(); ptr != NULL; ptr = ptr->getNextElement()){
        signallaufzeit[h]=0;
        vater[h]=NULL;

        h++;

    }

    DFS_Visit(gE->getStartElement(),gE->getStartElement());


}
void LaufzeitAnalysator::DFS_Visit(ListenElement* x,ListenElement* y){
    SchaltwerkElement * k = x->getSchaltwerkElement();
    SchaltwerkElement * s = y->getSchaltwerkElement();

    for(int i=0;i<k->getAnzahlNachfolger();i++){

        SchaltwerkElement* v =k->getNachfolger(i);

        if(v->getTyp()->getIsFlipflop()){
            if(laufzeitUebergangspfad<*signallaufzeit[i] + k->getLaufzeitEinzelgatter()){
                laufzeitUebergangspfad=*signallaufzeit[i] + k->getLaufzeitEinzelgatter();
//String erstellen
            }
        }

        else if(){

        }


    }

}
