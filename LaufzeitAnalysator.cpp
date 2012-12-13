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

void LaufzeitAnalysator::berechne_LaufzeitEinzelgatter()  /// berechnet Laufzeit fuer jedes einzelne Gatter
{
    double  spgFaktor,
            tmpFaktor,
            przFaktor;

    faktoren->getFaktoren(spgFaktor, tmpFaktor, przFaktor); /// holt sich aeussere Faktoren ueber Referenz

    cout << "INFO: SPG-F: "<<spgFaktor<<" TMP-F: "<<tmpFaktor<<" PRZ-F: "<<przFaktor<<endl<<endl;

    for (ListenElement* ptr = gE->getStartElement(); ptr != NULL; ptr = ptr->getNextElement()) /// durchlaeuft die ListenElemente und weist jedem Schaltwerk im Listenelement seine
    {

        double tpd0 = ptr->getSchaltwerkElement()->getTyp()->getGrundLaufzeit();     /// Grundlaufzeit  tpd0 (in ps) und seinen
        double lastFaktor = ptr->getSchaltwerkElement()->getTyp()->getLastFaktor();     /// Lastfaktor lastFaktor (in fs/fF) zu
        double last_C = 0;

        for (int i = 0; i < (ptr->getSchaltwerkElement()->getAnzahlNachfolger()); i++ )   /// summiert die Eingangs-C (in fF) der mit dem Ausgang verbundenen Gatter und
        {

            last_C = last_C + ptr->getSchaltwerkElement()->getNachfolger(i)->getTyp()->getLastKapazitaet();  /// speichert diese im Schaltwerkelement
            cout <<"INFO: C-Last: \t"<<last_C<<endl;

        }
        /// t_pd,actual = (t_pd0 + LastF + LastC) * TempF * SpgF * PrzF
        //  (ps)       = ( ps  + (fs/fF)  * fF  * 1000)   //wieso funkionierts mit 1/1000  und nicht mit 1000 ???????
        ptr->getSchaltwerkElement()->setLaufzeitEinzelgatter(((tpd0 + lastFaktor * last_C * 0.001) * spgFaktor * tmpFaktor * przFaktor));  /// berechnet die Gesamtlaufzeit des Einzelgatters

        cout << "INFO: Laufzeit Einzelgatter von "<< ptr->getSchaltwerkElement()->getName() << ":\t"<<ptr->getSchaltwerkElement()->getLaufzeitEinzelgatter()<<endl;
    }

}


void LaufzeitAnalysator::DFS(ListenElement* s)
{
    int h=0;

    for (ListenElement* ptr = gE->getStartElement(); ptr != NULL; ptr = ptr->getNextElement())
    {
        signallaufzeit[h]=0;
        vater[h]=NULL;

        h++;

    }

    DFS_Visit(gE->getStartElement(),gE->getStartElement());


}
void LaufzeitAnalysator::DFS_Visit(ListenElement* x,ListenElement* y)
{
    SchaltwerkElement * k = x->getSchaltwerkElement();
    SchaltwerkElement * s = y->getSchaltwerkElement();

    for (int i=0;i<k->getAnzahlNachfolger();i++)
    {

        SchaltwerkElement* v =k->getNachfolger(i);

        if (v->getTyp()->getIsFlipflop())
        {
            if (laufzeitUebergangspfad<*signallaufzeit[i] + k->getLaufzeitEinzelgatter())
            {
                laufzeitUebergangspfad=*signallaufzeit[i] + k->getLaufzeitEinzelgatter();
//String erstellen
            }
        }

        /*else if ()
        {

        }*/


    }

}
