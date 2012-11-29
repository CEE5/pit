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

//noch keine ahnung wie die funktionam ende aussieht
bool GraphErzeuger::graphErzeugen(SignalListeErzeuger signallist){
//SignalListeErzeuger signallist;
for (int i = 0; i < signallist.getAnzahlSignale(); i++) {
    Signal tmpSignal = *signallist.getSignal( i );
    ListenElement* newListenElement = new ListenElement();
    SchaltwerkElement* newSchaltwerkElement = new SchaltwerkElement( (*bibliothek).getBibElement( tmpSignal.getQuellenTyp() ));

    newListenElement->setSchaltwerkElement( newSchaltwerkElement );
    newSchaltwerkElement->setName(tmpSignal.getQuelle());
    newSchaltwerkElement->setAnzahlNachfolger(tmpSignal.getAnzahlZiele());
    if(tmpSignal.getSignalTyp() == eingang ) {
        newSchaltwerkElement->setIsEingangsElement(true);
        cout <<"INFO: eingang gefunden"<<endl;
    }
    if(tmpSignal.getSignalTyp() == ausgang ) {
        newSchaltwerkElement->setIsAusgangsElement(true);
        cout <<"INFO: ausgang gefunden"<<endl;
    }
    cout <<"INFO: "<<i<<". ListenElement angelegt"<<endl;

}
 return 0;
}
