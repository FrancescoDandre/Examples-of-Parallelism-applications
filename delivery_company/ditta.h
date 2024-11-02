#include <string>
using namespace std;
/*class Product{
    private:
    string name;//nome inteso come identificativo
    int size_p; // quantità (casse/lotti)
    int time; // tempo di scarico per cassa/lotto
    public:
    Product(string name, int size_p, int time){
        this->name=name;
        this->size_p=size_p;
        this->time=time;
    }
    Product();
    string name(){return name;}
    int size_p(){return size_p;}
    int time(){return time;}
};*/

class Magazzino{
    protected:
    string city; //città dove è situato
    int size; //numero di casse totali che può contenere
    int n_products; //numero prodotti diversi
    string* name_products; //nome prodotti
    int* quantity_products; // quantità prodotti
    int tot_products;// numero totale di prodotti
    public:
    Magazzino(string city, int size);
    Magazzino(){}//mi serve solo per la parte parallela
    void fill(string p, int n);
    //void give(Product p);
    void info();
};

struct Ordine{
    string name_p; //nome prodotto
    int n; //numero di casse/lotti
    string city; //città dove effettuare la consegna 
    int time;//tempo impiegato (minuti) per scaricare a lotto 
    bool stato=0; //0 non completato, 1 completato
    //int guadagno; //guadagno ottenuto una volta effettuata la consegna
};

Ordine newOrder(string p, int n, string city, int time);
void Order_info(Ordine o);

struct Route {
    string partenza; //deve essere una città con un magazzino della compagnia
    string arrivo; //come sopra
    Magazzino* m;//magazzino dove effettuare la consegna
    int distanza; //distanza in km
    //supponiamo di percorrere 1000 km al giorno, raggiunti i quali è previsto un riposo di otto ore
    int confini_attraversati; //supponiamo 20 minuti di attesa/controlli alle dogane
    //int tappe_intermedie; 
    Ordine* o;//ordine per il quale si effettua il viaggio
};

class Camion{
    private:
    int size; //numero di casse totali che può contenere
    int n_products; //numero prodotti diversi
    string* name_products; //nome prodotti
    int* quantity_products; // quantità prodotti
    int tot_products;// numero totale di prodotti
    int speed; // velocità media in km/h
    bool in_corsa;//1 se sta viaggiando, 0 se è disponibile
    bool CompProperty;
    public:
    Camion(int size, int speed);
    Camion(){}//mi serve solo per la parte parallela
    void fill(string p, int n);
    void give(string p, int n);
    int velocity(){return speed;}
    int dim(){return size;}
    bool state(){return in_corsa;}
    void info();
    void change_stato(bool b){in_corsa=b;}
    bool operator==(Camion c){
        bool b=0;
        if(this->size==c.size && this->n_products==c.n_products && this->name_products==c.name_products && this->quantity_products==c.quantity_products && this->tot_products==c.tot_products && this->speed==c.speed && this->in_corsa==c.in_corsa) b=1;
        return b;
    }
};

class Delivery_Company {
    private:
    Magazzino** magazzini; //array di puntatori
    int n_magazzini;
    Ordine** ordini;//array di puntatori a ordini
    int n_ordini;//numero consegne da effettuare
    Camion** trucks; //array di puntatori a camion
    int n_camion;//numero di camion disponibili per il trasporto
    public:
    Delivery_Company();
    void add_magazzino(Magazzino& m);
    void add_camion(Camion& c);
    void Order(Ordine&);
    void seeOrders();
    Route planRoute(string partenza, string arrivo, Magazzino& m, int distanza, Ordine& o, int confini=0);
    void timeForecast(Route, Camion, int t[3]);//previsione del tempo totale, in viaggio e tracosrso fermi (per fermate dovute a dogane, riposo autista e scarico merci)
    void execute(Route& , Camion& c, int t[3]);// esegue l'ordine (stato Ordine e Camion a 1) e in t restituisce il tempo effettivo

};
