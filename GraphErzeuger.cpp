#include "GraphErzeuger.h"

GraphErzeuger::GraphErzeuger(){

}


/** Destruktor der Klasse.*/
GraphErzeuger::~GraphErzeuger(){

}

Bibliothek* GraphErzeuger::getBibliothek(){
    return bibliothek;
}

void GraphErzeuger::setBibliothek( Bibliothek biblio){
    bibliothek = &biblio;
}

/*ListenElement* GraphErzeuger::getStartElement(){
    return startElement;
}

void GraphErzeuger::setStartElement( ListenElement* start){
    startElement = start;
}

ListenElement* GraphErzeuger::getEndElement(){
    return endElement;
}

void GraphErzeuger::setEndElement( ListenElement* ende){
    endElement = ende;
}*/


//noch keine ahnung wie die funktionam ende aussieht
void GraphErzeuger::graphErzeugen(SignalListeErzeuger signallist){    // da stimmt noch so einiges ned und fehlt noch einiges
//SignalListeErzeuger signallist;
//ListenElement* tmpListenElement = NULL;
int j=1;
for (int i = 0; i < signallist.getAnzahlSignale(); i++) {
    Signal tmpSignal = *signallist.getSignal( i );

    if((tmpSignal.getSignalTyp() == eingang) or (tmpSignal.getSignalTyp() == clk) ) {
        //newSchaltwerkElement->setIsEingangsElement(true);
        cout <<"INFO: eingang oder clock gefunden"<<endl;
    }else{
        GatterTyp* tmpGatter = bibliothek->getBibElement(tmpSignal.getQuellenTyp());

        ListenElement* newListenElement = new ListenElement();
        SchaltwerkElement* newSchaltwerkElement = new SchaltwerkElement( tmpGatter );

    newSchaltwerkElement->setName(tmpSignal.getQuelle());
    newSchaltwerkElement->setAnzahlNachfolger(tmpSignal.getAnzahlZiele());
    newSchaltwerkElement->setLaufzeitEinzelgatter( tmpGatter->getGrundLaufzeit() );
    newSchaltwerkElement->setAnzahlEingangssignale( tmpGatter->getEingaenge());

    if(tmpSignal.getSignalTyp() == ausgang ) {
        newSchaltwerkElement->setIsAusgangsElement(true);
        cout <<"INFO: ausgang gefunden"<<endl;
    }
    newListenElement->setSchaltwerkElement( newSchaltwerkElement );
    cout <<"INFO: "<<j++<<". ListenElement angelegt vom Typ "<< tmpSignal.getQuellenTyp()<<endl;

    if( endElement == NULL ){
    newListenElement->setNextElement( NULL );
    endElement = newListenElement;
    startElement = newListenElement;
    } else {
    newListenElement->setNextElement( startElement );
    startElement = newListenElement;
    }
    /*if ( i == 1) {
        startElement = newListenElement;
        cout << "start gefunden"<<endl;
    }
    else if (i == signallist.getAnzahlSignale()-1 ) {
        endElement = newListenElement;
    }


    if ( i != 1 ) {
        tmpListenElement->setNextElement( newListenElement ) ;
    }

    tmpListenElement = newListenElement;*/
    }
}
  // soll am ende eigentlich startzeiger zurueckgeben
}


 void GraphErzeuger::listenAusgabe ( ){

    for(ListenElement* ptr = startElement; ptr != NULL; ptr = ptr->getNextElement()) {
        SchaltwerkElement* tmpSWE = ptr->getSchaltwerkElement();
        cout << "--"<<endl<<    tmpSWE->getName() <<endl
        <<"LaufzeitEinzelgatter: \t"<< tmpSWE->getLaufzeitEinzelgatter() <<endl
        <<"IsEingangsElement: \t"<< tmpSWE->getIsEingangsElement() <<endl
        <<"IsAusgangsElement: \t"<< tmpSWE->getIsAusgangsElement() <<endl
        <<"AnzahlEingangssignale: \t"<< tmpSWE->getAnzahlEingangssignale() <<endl
        <<"AnzahlNachfolger: \t"<< tmpSWE->getAnzahlNachfolger() <<endl;
    }
}
