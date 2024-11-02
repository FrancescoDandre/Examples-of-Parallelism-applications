#include "trains.h"

Vagone::Vagone(bool tipo){
    this->tipo=tipo;
}

void Vagone::link_to_train(Treno& t){
    treno_di_appartenenza=&t;
    ID_treno=t.show_ID();
    destinazione_treno=t.show_destinazione();
}

void Vagone::info_vagone(){
    string type;
    if(tipo==0) type="merci";
    else type="passeggeri";
    cout<<type;
    cout<<endl;
    cout<<"ID treno di appartenenza: "<<ID_treno<<endl;
    cout<<"Destinazione: "<<destinazione_treno<<endl;
}

Treno::Treno(int ID, string origine, string destinazione){
    this->ID=ID;
    this->origine=origine;
    this->destinazone=destinazione;
}

void Treno::add_vagone(Vagone& v){
    train.push_back(&v);
    v.link_to_train(*this);
}

void Treno::add_vagone_copia(Vagone& v){ //copio il vagone invece che inserire il riferimento
    v.link_to_train(*this);
    train2.push_back(v);
}

void Treno::info_treno(){
    cout<<endl<<"TRENO:"<<endl;
    cout<<"lunghezza: "<<train.size()<<" vagoni"<<endl;
    cout<<"ID: "<<ID<<endl;
    cout<<"Origine: "<<origine<<endl;
    cout<<"Destinazione: "<<destinazone<<endl;
    for(int i=0;i<train.size(); i++){
        cout<<"Vagone "<<i+1<<endl;
        train[i]->info_vagone();
    }
}

void Treno::info_treno2(){ 
    cout<<endl<<"TRENO:"<<endl;
    cout<<"lunghezza: "<<train2.size()<<" vagoni"<<endl;
    cout<<"ID: "<<ID<<endl;
    cout<<"Origine: "<<origine<<endl;
    cout<<"Destinazione: "<<destinazone<<endl;
    for(int i=0;i<train2.size(); i++){
        cout<<"Vagone "<<i+1<<endl;
        train2[i].info_vagone();
    }
}

