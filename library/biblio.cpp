#include "biblio.h"
#include <iostream>
using namespace std;

Book::Book(string titolo, string autore,int anno_pubblicazione, int copie){
    this->titolo=titolo;
    this->autore = autore;
    this->anno_pubblicazione = anno_pubblicazione;
    this->copie = copie;
    copie_disponibili=copie;
    copie_prestate=0;
    n_lettori=0;
    lettori=new string [1];
    lettori[0]="nessuno";
    stato=0;
}

Book::Book(){
    stato=1;
}
/*
void Book::presta(char* lettore, int copie_prestate){
    char** l= new char*[n_lettori];
    for (int i=0; i<n_lettori; i++){
        l[i] = lettori[i];
    }
    delete[] lettori;
    lettori=new char* [n_lettori+1];
    for (int i=0; i<n_lettori; i++){
        lettori[i]=l[i];
    }
    lettori[n_lettori]=lettore;
    n_lettori+=1;
    this->copie_prestate += copie_prestate;
    copie_disponibili -= copie_prestate;

}
*/
int Book::presta(Cliente lettore, int copie_prestate){
    if(copie_disponibili<1) {cout<<"non ci sono copie disponibili"<<endl;return -1;}
    if (copie_disponibili<copie_prestate) {cout<<"non ci sono "<<copie_prestate<<" copie disponibili, ma solo "<<copie_disponibili<<endl;return -1;}

    string* l= new string[n_lettori];
    for (int i=0; i<n_lettori; i++){
        l[i] = lettori[i];
    }
    delete[] lettori;
    lettori=new string [n_lettori+1];
    for (int i=0; i<n_lettori; i++){
        lettori[i]=l[i];
    }
    lettori[n_lettori]=lettore.nome_e_cognome();
    n_lettori+=1;
    this->copie_prestate += copie_prestate;
    copie_disponibili -= copie_prestate;
    //lettore.legge(this->Book)
    return 0;
}

void Book::info(){
    cout<<endl;
    cout<<"Titolo: "<<this->titolo<<endl;
    cout<<"Autore: "<<this->autore<<endl;
    cout<<"Anno di pubblicazione: "<<anno_pubblicazione<<endl;
    cout<<"Copie disponibili: "<<copie_disponibili<<endl;
    cout<<"Copie prestate: "<<copie_prestate<<endl;
    cout<<"Lettori: ";
    for (int i=0; i<n_lettori; i++){
        cout<<lettori[i]<<" ";
    }
    cout<<endl<<endl;
}

bool Book::leggi_stato(){
    return stato;
}

void Book::modifica_stato(bool a){
    stato=a;
}

bool Book::operator==(Book a){
    if(a.titolo==titolo && a.autore==autore && a.anno_pubblicazione==anno_pubblicazione) return 1;
    return 0;
}

string Book::leggi_titolo(){
    return titolo;
}

string Book::leggi_autore(){
    return autore;
}

int Book::leggi_anno_pubblicazione(){
    return anno_pubblicazione;
}

void Book::add_copie(int c){
    copie+=c;
    copie_disponibili+=c;
}

void Book::remove_copie(int c){
    copie-=c;
    copie_disponibili-=c;
}

int Book::leggi_copie(){
    return copie;
}

Cliente::Cliente(string nome, string cognome){
    this->nome=nome;
    this->cognome=cognome;
    n_libri=0;
    libri= new Book*[0];
}

Cliente::Cliente(){};

void Cliente::legge(Book& b){
   Book** l= new Book*[n_libri];
    for (int i=0; i<n_libri; i++){
        l[i] = libri[i];
    }
    delete[] libri;
    libri=new Book* [n_libri+1];
    for (int i=0; i<n_libri; i++){
        libri[i]=l[i];
    }
    libri[n_libri]=&b;
    n_libri+=1;   
}

string Cliente::nome_e_cognome(){
    return string(nome)+" "+string(cognome);
}

void Cliente::info(){
    cout<<"Nome: "<<nome<<endl;
    cout<<"Cognome: "<<cognome<<endl;
    cout<<"libri in prestito: "<<n_libri<<endl;
    cout<<"Libri:"<<endl;
    for (int i=0; i<n_libri; i++){
        cout<<i+1<<".";
        (*libri[i]).info();
    }
}
/*
void Cliente::aggiorna_libro(Book& b){
    for(int i=0; i<n_libri; i++){
        if((*libri[i]).leggi_titolo()==b.leggi_titolo() && (*libri[i]).leggi_autore()==b.leggi_autore() && (*libri[i]).leggi_anno_pubblicazione()==b.leggi_anno_pubblicazione()) {
            libri[i]=&b;
            return;
        }
    }
}*/

Biblioteca::Biblioteca(int size){
    biblio = new Book[size];
    this->size=size;
    posti_disponibili=size;
    n_clienti=0;
    clientela=new Cliente[0];
}

void Biblioteca::add_book(Book& b, int c){
    for(int i=0; i<size; i++){
        if (biblio[i]==b) {
            b.add_copie(c);
            biblio[i]=b;
            return;
        }
    }
    for(int i=0; i<size; i++){
        if (biblio[i].leggi_stato()==1) {
            biblio[i]=b;
            posti_disponibili-=1;
            break;
        }
    }
}

void Biblioteca::remove_book(Book& b,int c){
    for(int i=0; i<size; i++){
        if (biblio[i]==b) {
            b.remove_copie(c);
            biblio[i].remove_copie(c);
            if(biblio[i].leggi_copie()<1){
                biblio[i].modifica_stato(1);
                posti_disponibili+=1;
                break;
            }
            break;
        }
    }
}

void Biblioteca::biblio_info(){
    cout<<endl<<"Info Biblioteca"<<endl<<"libri posseduti: "<<size-posti_disponibili;
    int count=0;
    for (int i=0; i<size; i++){
        if (biblio[i].leggi_stato()==0) {count=count+biblio[i].leggi_copie();}
    }
    cout<<endl<<"numero di volumi totali: "<<count;;
    for (int i=0; i<size; i++){
        if (biblio[i].leggi_stato()==0) {cout<<endl<<i+1<<".";biblio[i].info();}
    }
    cout<<"Clienti: ";
    for (int i=0; i<n_clienti; i++){
        cout<<endl<<i+1<<". "<<clientela[i].nome_e_cognome();
    }
    cout<<endl<<endl;
}

void Biblioteca::add_cliente(Cliente& c){
    Cliente* l= new Cliente[n_clienti];
    for (int i=0; i<n_clienti; i++){
        l[i] = clientela[i];
    }
    delete[] clientela;
    clientela=new Cliente[n_clienti+1];
    for (int i=0; i<n_clienti; i++){
        clientela[i]=l[i];
    }
    clientela[n_clienti]=c;
    n_clienti+=1;  
}

void Biblioteca::search_titolo(string titolo){
    int count=0;
    for (int i=0; i<size; i++){
        if(biblio[i].leggi_stato()==0 && biblio[i].leggi_titolo().find(titolo)!=-1) {biblio[i].info();} //return;}
        else count++;
    }
    if(count==size) cout<<titolo<<": libro non trovato"<<endl;
}

void Biblioteca::search_cognome_autore(string cognome_autore){
    int count=0;
    for (int i=0; i<size; i++){
        if(biblio[i].leggi_stato()==0 && biblio[i].leggi_autore().find(cognome_autore)!=-1) {biblio[i].info();} //return;}
        else count++;
    }
    if(count==size) cout<<cognome_autore<<": autore non trovato"<<endl;
}

void Biblioteca::search_anno_pubblicazione(int a, int b){
    int count=0;
    for (int i=0; i<size; i++){
        if(biblio[i].leggi_stato()==0 && biblio[i].leggi_anno_pubblicazione()>=a && biblio[i].leggi_anno_pubblicazione()<=b) {biblio[i].info();} //return;}
        else count++;
    }
    if(count==size) cout<<a<<"-"<<b<<": intervallo anno di pubblicazione non trovato"<<endl;
}

void Biblioteca::presta(Book& b, Cliente& c){
    if(b.presta(c,1)!=-1){
        c.legge(b);
        for (int i=0; i<size; i++){
            if(biblio[i].leggi_stato()==0 && biblio[i].leggi_titolo()==b.leggi_titolo() && biblio[i].leggi_autore()==b.leggi_autore() && biblio[i].leggi_anno_pubblicazione()==b.leggi_anno_pubblicazione()) biblio[i]=b; //return;}
        }
        //devo aggiornare anche l'info del libro dei clienti che hanno già in prestito una copia di questo libro
        /*for (int i=0; i<n_clienti; i++){
            clientela[i].aggiorna_libro(b);
        }*/ 
        //non serve più dato che ho risolto mettendo un array di puntatori a libri nella classe cliente: così facendo i libri sono sempre aggiornati, i puntatori puntano all'indirizzo di memoria 
    }
}
