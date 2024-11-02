#include "ditta.h"
#include <iomanip>
#include <iostream>
#include <cmath>

Magazzino::Magazzino(string city, int size){
    this->city=city;
    this->size=size;
    n_products=0;
    name_products=new string[0];
    quantity_products=new int[0];
    tot_products=0;
}

void Magazzino::fill(string p, int n){
    if (tot_products==size)  {cout<<"magazzino pieno"<<endl; return;}
    if (tot_products+n>=size) n=size-tot_products;
    for(int i=0; i<n_products; i++){
        if(name_products[i]==p) {quantity_products[i]+=n; tot_products+=n; return;} 
    }
    string* new_name_p= new string[n_products];
    int* new_quantity_p= new int[n_products];
    for (int i=0; i<n_products; i++){
        new_name_p[i] = name_products[i];
        new_quantity_p[i] = quantity_products[i];
    }
    delete[] name_products;
    delete[] quantity_products;
    name_products= new string[n_products+1];
    quantity_products= new int[n_products+1];
    for (int i=0; i<n_products; i++){
        name_products[i]=new_name_p[i];
        quantity_products[i]=new_quantity_p[i];
    }
    delete[] new_name_p;
    delete[] new_quantity_p;
    name_products[n_products]=p;
    quantity_products[n_products]=n;
    n_products+=1;
    tot_products+=n;
}

void Magazzino::info(){
    cout<<endl<<"Magazzino: "<<endl;
    cout<<"city: "<<city<<endl;
    cout<<"size: "<<size<<endl;
    cout<<"numero di prodotti diversi contenuti: "<<n_products<<endl;
    cout<<"lotti totali contenuti: "<<tot_products<<endl;
    for(int i=0; i<n_products; i++){
        cout<<setw(15)<<name_products[i];
    }
    cout<<endl;
    for(int i=0; i<n_products; i++){
        cout<<setw(15)<<quantity_products[i];
    }
    cout<<endl;
}

Delivery_Company::Delivery_Company(){
    n_magazzini=0;
    magazzini= new Magazzino* [0];
    n_ordini=0;
    ordini=new Ordine*[0];
    n_camion=0;
    trucks= new Camion*[0];
}

void Delivery_Company::add_magazzino(Magazzino& m){
    Magazzino** new_magazzini = new Magazzino* [n_magazzini];
    for(int i=0; i<n_magazzini; i++){
        new_magazzini[i]=magazzini[i];
    }
    delete[] magazzini;
    magazzini= new Magazzino*[n_magazzini+1];
    for(int i=0; i<n_magazzini; i++){
        magazzini[i]=new_magazzini[i];
    }
    delete[] new_magazzini;
    magazzini[n_magazzini]=&m;
    n_magazzini+=1;
}

Ordine newOrder(string p, int n, string city, int time){
    Ordine o;
    o.name_p=p;
    o.n=n;
    o.city=city;
    o.time=time;
    return o;
}

void Order_info(Ordine o){
    cout<<endl<<"Ordine: "<<endl;
    cout<<o.n<<" "<<o.name_p<<endl<<o.city<<endl;
}

void Delivery_Company::Order(Ordine& ord){
    Ordine** new_ordini= new Ordine*[n_ordini];
    for(int i=0; i<n_ordini; i++){
        new_ordini[i]= ordini[i];
    }
    delete[] ordini;
    ordini=new Ordine*[n_ordini+1];
    for(int i=0; i<n_ordini; i++){
        ordini[i]=new_ordini[i];
    }
    delete[] new_ordini;
    ordini[n_ordini]=&ord;
    n_ordini+=1;
}

void Delivery_Company::seeOrders(){
    bool ordini_in_attesa=0;
    for(int i=0; i<n_ordini; i++){
        if(ordini[i]->stato==0) {Order_info(*ordini[i]);ordini_in_attesa=1;}
    }
    if(ordini_in_attesa==0) cout<<"nessun ordine in attesa"<<endl;
}

Route Delivery_Company::planRoute(string partenza, string arrivo, Magazzino& m, int distanza, Ordine& o, int confini){
    Route r;
    r.partenza=partenza;
    r.arrivo=arrivo;
    r.m=&m;
    r.confini_attraversati=confini;
    r.distanza=distanza;
    r.o=&o;
    return r;
}

void Delivery_Company::timeForecast(Route r, Camion c, int t[3]){
    if(r.o->n>c.dim()) {cout<<"camion non abbastanza capiente"<<endl; return;}
    int time_p=0; //tempo fermi in minuti
    int time_v=(float(r.distanza)/float(c.velocity())) *60; //tempo in viaggio
    time_p+=r.o->time*r.o->n;
    time_p+=r.confini_attraversati*20;//supponiamo 20 minuti alla dogana
    int time_tot=time_p+time_v;
    time_p+=int(time_tot/60/16)*8*60;//tempo di riposo autista
    t[0]=time_p+time_v;
    t[1]= time_v;
    t[2]= time_p;
}

Camion::Camion(int size, int speed){
    this->size=size;
    this->speed=speed;
    n_products=0;
    name_products=new string[0];
    quantity_products=new int[0];
    tot_products=0;
    in_corsa=0;
}

void Camion::fill(string p, int n){
    if (tot_products==size)  {cout<<"camion pieno"<<endl; return;}
    if (tot_products+n>=size) n=size-tot_products;
    for(int i=0; i<n_products; i++){
        if(name_products[i]==p) {quantity_products[i]+=n; tot_products+=n; return;} 
    }
    string* new_name_p= new string[n_products];
    int* new_quantity_p= new int[n_products];
    for (int i=0; i<n_products; i++){
        new_name_p[i] = name_products[i];
        new_quantity_p[i] = quantity_products[i];
    }
    delete[] name_products;
    delete[] quantity_products;
    name_products= new string[n_products+1];
    quantity_products= new int[n_products+1];
    for (int i=0; i<n_products; i++){
        name_products[i]=new_name_p[i];
        quantity_products[i]=new_quantity_p[i];
    }
    delete[] new_name_p;
    delete[] new_quantity_p;
    name_products[n_products]=p;
    quantity_products[n_products]=n;
    n_products+=1;
    tot_products+=n;
}

void Camion::give(string p, int n){
    for(int i=0; i<n_products; i++){
        if(name_products[i]==p) {quantity_products[i]-=n; tot_products-=n; return;} 
    }
    cout<<"prodotto non presente nel camion"<<endl;
    return;
}

void Camion::info(){
    cout<<endl<<"Camion:"<<endl;
    cout<<"size: "<<size<<endl;
    cout<<"numero di prodotti diversi contenuti: "<<n_products<<endl;
    cout<<"lotti totali contenuti: "<<tot_products<<endl;
    for(int i=0; i<n_products; i++){
        cout<<setw(15)<<name_products[i];
    }
    cout<<endl;
    for(int i=0; i<n_products; i++){
        cout<<setw(15)<<quantity_products[i];
    }
    cout<<endl;
}

void Delivery_Company::add_camion(Camion& c){
    Camion** new_trucks = new Camion* [n_camion];
    for(int i=0; i<n_camion; i++){
        new_trucks[i]=trucks[i];
    }
    delete[] trucks;
    trucks= new Camion*[n_camion+1];
    for(int i=0; i<n_camion; i++){
        trucks[i]=new_trucks[i];
    }
    delete[] new_trucks;
    trucks[n_camion]=&c;
    n_camion+=1;
}

void Delivery_Company::execute(Route& r, Camion& c, int t[3]){

    bool Company_camion=0;//verifico che il camion sia della compagnia
    for(int i=0; i<n_camion; i++){
        if(*trucks[i]==c) {Company_camion=1; break;}
    }
    if(Company_camion==0) {cout<<"il camion non appartiene alla ditta"<<endl;return;}
    if(c.state()==1) {cout<<"camion occupato"<<endl;return;}

    c.change_stato(1);//il camion è partito, perciò è occupato
    c.give(r.o->name_p, r.o->n);//camion consegna il prodotto
    r.m->fill(r.o->name_p, r.o->n);//riempio il magazzino

    r.o->stato=1;//ordine completato

    timeForecast(r,c,t);
    srand((int)time(NULL));
    for(int i=0; i<5; i++) rand();//per avere i numeri dopo più diversi tra loro tra un esecuzione e l'altra
    float ritardo_casuale1=static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/0.4))-0.1;
    t[1]=round(float(t[1])+(ritardo_casuale1)*float(t[1]));
    float ritardo_casuale2=static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/0.4))-0.1;
    t[2]=round(float(t[2])+(ritardo_casuale2)*float(t[2]));
    t[0]=t[1]+t[2];
}