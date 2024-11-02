using namespace std;
#include <string>
class Cliente;
class Book{
    private:
    string titolo;
    string autore;
    int anno_pubblicazione;
    int copie_disponibili;
    int copie_prestate;
    int n_lettori;
    string* lettori;
    int copie;
    bool stato;// se il libro non è ancora stato scritto =1, in caso contrario 0
    public:
    Book(string titolo, string autore,int anno_pubblicazione, int copie=1);
    Book();
    //void presta(char* lettore, int copie_prestate);
    int presta(Cliente lettore, int copie_prestate);
    void info();
    bool leggi_stato();
    void modifica_stato(bool a);
    bool operator==(Book a);
    string leggi_titolo();
    string leggi_autore();
    int leggi_anno_pubblicazione();
    void add_copie(int c);
    void remove_copie(int c);
    int leggi_copie();
};

class Cliente{
    private:
    string nome;
    string cognome;
    int n_libri;
    Book** libri;  //puntatori di puntatori usati come array di puntatori a libri;
    public:
    Cliente(string nome, string cognome);
    Cliente();
    void legge(Book& b);
    string nome_e_cognome();
    void info();
    /*void aggiorna_libro(Book& b);*/
};

class Biblioteca{
    private:
    int size;
    int posti_disponibili; //per libri diversi
    Book* biblio;
    int n_clienti;
    Cliente* clientela; 
    public:
    Biblioteca(int size);//numero di libri diversi posseduti dalla biblioteca
    void biblio_info();
    void add_book(Book& b, int c=1);
    void remove_book(Book& b, int c=1);
    void add_cliente(Cliente& c);
    void search_titolo(string titolo);
    void search_cognome_autore(string cognome_autore);
    void search_anno_pubblicazione(int a, int b);
    void presta(Book& b, Cliente& c);
};