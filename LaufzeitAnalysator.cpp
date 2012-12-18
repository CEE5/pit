#include "LaufzeitAnalysator.h"



LaufzeitAnalysator::LaufzeitAnalysator(GraphErzeuger* g, Faktoren* f)
{

    faktoren = f;
    gE = g;

    *signallaufzeit = new double[gE->getGatterAnzahl()];
    *vater = new int [gE->getGatterAnzahl()];

    laufzeitUebergangspfad=0;


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

    DFS_Visit(gE->getStartElement()->getSchaltwerkElement(),gE->getStartElement()->getSchaltwerkElement());


}
bool LaufzeitAnalysator::zyklensuche(SchaltwerkElement* se){

}
void LaufzeitAnalysator::DFS_Visit(SchaltwerkElement* k,SchaltwerkElement* s)
{
 //   SchaltwerkElement * k = x->getSchaltwerkElement();
   // SchaltwerkElement * s = y->getSchaltwerkElement();

    bool zykBreak = true;
    for (int i=0; i<k->getAnzahlNachfolger()and zykBreak; i++)
    {

        SchaltwerkElement* v =k->getNachfolger(i);

        if (v->getTyp()->getIsFlipflop())
        {
            if (laufzeitUebergangspfad<DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter())
            {
                laufzeitUebergangspfad=DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();

                uebergangspfad = k->getName() + " ->" + k->getNachfolger(i)->getName();
//String erstellen
            }
        }

        else if (DFS_Zwischenspeicher[k->getNachfolger(i)].PfadLaufzeit < (DFS_Zwischenspeicher[k].PfadLaufzeit +k->getLaufzeitEinzelgatter()))
        {
            if( ( ( DFS_Zwischenspeicher[ v ].PfadLaufzeit != 0 ) or ( v== s ) ) and ( DFS_Zwischenspeicher[ v ].VaterElement != k) )
            {
                DFS_Zwischenspeicher[v].VaterElement =k;


                if(zyklensuche(v))
            {
                zykBreak = false;
                cout << "Fehler Zyklensuche"<<endl;

            }
        }
        DFS_Zwischenspeicher[v].PfadLaufzeit = DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();
            DFS_Zwischenspeicher[v].VaterElement = k;

            DFS_Visit(v,s);

        }


    }
    if(k->getIsAusgangsElement() and (laufzeitAusgangspfad < (DFS_Zwischenspeicher[k].PfadLaufzeit+k->getLaufzeitEinzelgatter())))
    {
        laufzeitAusgangspfad= DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();

        ausgangspfad =k->getName();

        for(SchaltwerkElement * j = k; j != s; j= DFS_Zwischenspeicher[j].VaterElement)
        {
            ausgangspfad.insert(0,(DFS_Zwischenspeicher[j].VaterElement->getName() + "->"));
        }
    }

}
