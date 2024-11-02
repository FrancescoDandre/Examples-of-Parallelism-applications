using namespace std;
#include <iostream>
#include<vector>
#include <string>

class Treno;

class Vagone{
    private:
    bool tipo; //0 merci, 1 passeggeri
    int ID_treno;
    string destinazione_treno;
    Treno* treno_di_appartenenza;
    public:
    Vagone(){}
    Vagone(bool tipo);
    void set_tipo(bool b){tipo=b;}
    void link_to_train(Treno& t);
    void info_vagone();
};

class Treno{
    private:
    vector<Vagone*> train;
    vector<Vagone> train2;//usato per inserire le copie invece che i puntatori
    string origine;
    string destinazone;
    int ID;
    public:
    Treno(int ID, string origine, string destinazione);
    void add_vagone(Vagone& v);
    void add_vagone_copia(Vagone& v); //inserisco il vagone copiandolo
    int show_ID(){return ID;}
    string show_destinazione(){return destinazone;}
    int lunghezza(){return train.size();}
    void info_treno();
    void info_treno2();//per visualizzare il treno quando i vagoni sono stati inseriti per copia
};