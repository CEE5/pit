#include "LaufzeitAnalysator.h"



LaufzeitAnalysator::LaufzeitAnalysator(GraphErzeuger* g, Faktoren* f)
{

    faktoren = f;
    gE = g;

    *signallaufzeit = new double[gE->getGatterAnzahl()];
    *vater = new int [gE->getGatterAnzahl()];

    laufzeitUebergangspfad=0;
DFS_Zwischenspeicher.clear();

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
void LaufzeitAnalysator::DFS_startSuche(GraphErzeuger *gE){

     vector < ListenElement *> start;

    for(ListenElement *i= gE->getStartElement(); i!=NULL;i=i->getNextElement()){
        if(i->getSchaltwerkElement()->getIsEingangsElement() or i->getSchaltwerkElement()->getTyp()->getIsFlipflop()){
            cout <<&i<<endl;
            start.push_back(i);
        }
    }



        DFS(start.at(0));
        cout <<endl<<endl<<endl<<endl;
        DFS(start.at(1));



}

void LaufzeitAnalysator::DFS(ListenElement* s)
{


    for (ListenElement* ptr = gE->getStartElement(); ptr != NULL; ptr = ptr->getNextElement())
    {
        DFS_Zwischenspeicher[ptr->getSchaltwerkElement()].PfadLaufzeit =0.0;
        DFS_Zwischenspeicher[ptr->getSchaltwerkElement()].VaterElement = NULL;


    }

    DFS_Visit(gE->getStartElement()->getSchaltwerkElement(),gE->getStartElement()->getSchaltwerkElement());


}
bool LaufzeitAnalysator::zyklensuche(SchaltwerkElement* se){
    return false;

}
int count =0;
void LaufzeitAnalysator::DFS_Visit(SchaltwerkElement* k,SchaltwerkElement* s)
{cout <<count<<" k: "<<k->getName()<<endl;
    count++;
 //   SchaltwerkElement * k = x->getSchaltwerkElement();
   // SchaltwerkElement * s = y->getSchaltwerkElement();

    bool zykBreak = true;
    for (int i=0; ((i<(k->getAnzahlNachfolger()))and zykBreak); i++)
    {

        if(i==1){
        cout <<"x"<<endl;
        }

        SchaltwerkElement* v =k->getNachfolger(i);
        cout << "nachfolger:"<<v->getName()<<endl;

        if (v->getTyp()->getIsFlipflop())
        {
            cout <<"ff gefunden: "<<v->getName()<<endl;

            if (laufzeitUebergangspfad<DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter())
            {
                laufzeitUebergangspfad=DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();

                uebergangspfad = k->getName() + " ->" + k->getNachfolger(i)->getName();
                cout << "Übergangspfad: "<<uebergangspfad<<endl;
//String erstellen
            }
        }

        else if (DFS_Zwischenspeicher[v].PfadLaufzeit < (DFS_Zwischenspeicher[k].PfadLaufzeit +k->getLaufzeitEinzelgatter()))
        {
            cout << "v L < k L + kLE"<<endl;
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

    if(k->getIsAusgangsElement() and (laufzeitAusgangspfad < (DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter())))
    {
        laufzeitAusgangspfad= DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();

        ausgangspfad =k->getName();

        for(SchaltwerkElement * j = k; j != s; j= DFS_Zwischenspeicher[j].VaterElement)
        {
            ausgangspfad.insert(0,(DFS_Zwischenspeicher[j].VaterElement->getName() + "->"));
        }
        cout<<ausgangspfad<<endl;
    }

}
