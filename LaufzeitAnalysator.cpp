#include "LaufzeitAnalysator.h"



LaufzeitAnalysator::LaufzeitAnalysator(GraphErzeuger* g, Faktoren* f)
{

    faktoren = f;
    gE = g;



    laufzeitUebergangspfad=0;
    laufzeitAusgangspfad=0;
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
bool LaufzeitAnalysator::DFS_startSuche(GraphErzeuger *gE)
{

    vector < ListenElement *> start;

    for(ListenElement *i = gE->getStartElement(); i!=NULL ; i=i->getNextElement())
    {

        if(i->getSchaltwerkElement()->getIsEingangsElement() or i->getSchaltwerkElement()->getTyp()->getIsFlipflop())
        {


            start.push_back(i);
        }
    }




    for(int h=0; h<start.size(); h++)
    {

        DFS(start[h]);
    }


    return !zyklusFound;




}

void LaufzeitAnalysator::DFS(ListenElement* s)
{


    for (ListenElement* ptr = s; ptr != NULL; ptr = ptr->getNextElement())
    {
        DFS_Zwischenspeicher[ptr->getSchaltwerkElement()].PfadLaufzeit =0.0;
        DFS_Zwischenspeicher[ptr->getSchaltwerkElement()].VaterElement = NULL;


    }

    DFS_Visit(s->getSchaltwerkElement(),s->getSchaltwerkElement());


}

bool LaufzeitAnalysator::zyklensuche(SchaltwerkElement* se)
{
    for(SchaltwerkElement* i=se ; i!=NULL ; i=DFS_Zwischenspeicher[i].VaterElement)
    {
        if( DFS_Zwischenspeicher[i].VaterElement == se )
        {
            return true;
        }
    }
    return false;
}




void LaufzeitAnalysator::DFS_Visit(SchaltwerkElement* k,SchaltwerkElement* s)
{

    zyklusFound = false;
    for (int i=0; i<k->getAnzahlNachfolger(); i++)
    {
        if(zyklusFound)break;


        SchaltwerkElement* v =k->getNachfolger(i);
        cout << "nachfolger:"<<v->getName()<<endl;

        if (v->getTyp()->getIsFlipflop())
        {
            cout <<"ff gefunden: "<<v->getName()<<endl<<endl<<endl;

            if (laufzeitUebergangspfad<DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter())
            {
                laufzeitUebergangspfad=DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();

                uebergangspfad = k->getName() + " ->" + k->getNachfolger(i)->getName();
                //cout << "Übergangspfad: "<<uebergangspfad<<":"<<laufzeitUebergangspfad<<endl;
                //String erstellen
                for( SchaltwerkElement* v = k ; v != s ; v = DFS_Zwischenspeicher[v].VaterElement )
                {
                    uebergangspfad.insert( 0 , ( DFS_Zwischenspeicher[v].VaterElement->getName() + "-> " ));
                }

            }
        }

        else if (DFS_Zwischenspeicher[v].PfadLaufzeit < (DFS_Zwischenspeicher[k].PfadLaufzeit +k->getLaufzeitEinzelgatter()))
        {

            if( ( ( DFS_Zwischenspeicher[ v ].PfadLaufzeit != 0 ) or ( v== s ) ) and ( DFS_Zwischenspeicher[ v ].VaterElement != k) )
            {

                DFS_Zwischenspeicher[v].VaterElement =k;


                if(zyklensuche(v))
                {
                    zyklusFound = true;
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
        laufzeitAusgangspfad  = DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();

        ausgangspfad = k->getName();

        for(SchaltwerkElement * j = k; j != s; j= DFS_Zwischenspeicher[j].VaterElement)
        {
            ausgangspfad.insert(0,(DFS_Zwischenspeicher[j].VaterElement->getName() + "->"));
        }

    }

}

double LaufzeitAnalysator::maxFrequenz(long freq)
{

    cout << "Längster Pfad im Überfuehrungsschaltnetz:" << endl;
    cout << uebergangspfad << endl << endl;
    cout << "Maximale Laufzeit der Pfade im Überfuehrungsschaltnetz: " << laufzeitUebergangspfad << " ps" << endl;
    cout << endl;
    cout << "Längster Pfad im Ausgangsschaltnetz:" << endl;
    cout << ausgangspfad << endl << endl;
    cout << "Maximale Laufzeit der Pfade im Ausgangsschaltnetz: " << laufzeitAusgangspfad << " ps" << endl;
    cout << endl;
    cout << "-----------------------------------------------"<<endl;
    long double maxF = 1/ (dynamic_cast<Flipflop*>(( gE->getBibliothek()->getBibElement("dff")))->getSetupTime() * 0.000000000001 + laufzeitUebergangspfad * 0.000000000001 );

    if(maxF>1000){
        if(maxF>1000000){

        cout << "maxFrequenz: "<<maxF/1000000<<" MHz"<<endl;
        }
        else{
            cout << "maxFrequenz: "<<maxF/1000<<" kHz"<<endl;
        }
    }

    cout << "-----------------------------------------------"<<endl;
    if(maxF < freq){
        cout << "Frequenz zu groß"<<endl;
    }
    else{
        cout << "Frequenz okay"<<endl;

    }


}
