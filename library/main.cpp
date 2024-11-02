#include "biblio.h"
#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    //1.
    Book lotr("Lord of the rings", "Tolkien", 1967, 4);
    Book hobbit("The Hobbit", "Tolkien", 1964,3);
    Book gigant("Attack of the Giants", "Ken Follet", 2004,2);
    Book leoni("I leoni di Sicilia", "Oriana Fallaci", 2017);
    Biblioteca IlPonte(200);
    IlPonte.add_book(lotr);
    IlPonte.add_book(hobbit);
    IlPonte.add_book(gigant);
    IlPonte.add_book(leoni);
    
    //2. e 3.
    IlPonte.add_book(lotr,1);
    IlPonte.add_book(hobbit,1);
    IlPonte.add_book(gigant,3);
    IlPonte.add_book(leoni,5);
    IlPonte.biblio_info();

    //4.
    IlPonte.search_titolo("Lord");
    IlPonte.search_titolo("The Ancient Mariner");
    //5.
    IlPonte.search_cognome_autore("Leopardi");
    IlPonte.search_cognome_autore("Tolkien");
    //6.
    IlPonte.search_anno_pubblicazione(1900,2000);
    IlPonte.search_anno_pubblicazione(2000,2020);

    //7. e 8.
    Cliente Franz("Francesco", "Dandrea");
    Cliente Billy("Billy","IlFurbo");
    IlPonte.add_cliente(Franz);
    IlPonte.add_cliente(Billy);
    IlPonte.presta(lotr, Franz);
    IlPonte.presta(lotr, Billy);
    IlPonte.presta(leoni,Billy);
    //lotr.info();
    IlPonte.biblio_info(); 

    /*
    Franz.info();
    Billy.info();
    IlPonte.remove_book(lotr,4);
    IlPonte.biblio_info();
    Cliente Engel("Angelo", "Dandrea");
    IlPonte.add_cliente(Engel);
    IlPonte.presta(lotr,Engel);
    IlPonte.add_book(lotr,1);
    IlPonte.presta(lotr,Engel);
    IlPonte.add_book(lotr,1);
    IlPonte.biblio_info();
    IlPonte.presta(lotr,Engel);
    */

    //parallelismo, 2 agenti che lavorano in parallelo
    Cliente Engel("Angelo", "Dandrea");
    Book Commedia("Divina Commedia", "Dante Aligheri", 1300);
    Book Shock("Schock of vibrations", "Harris", 1995);
    Cliente Giorgio("Giorgio", "Chiellini");
    int flag1=0;
    int flag2=0;
    int temp_flag;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            IlPonte.add_book(Commedia);

            #pragma omp flush
            #pragma omp atomic write
            flag1 = 1;
            #pragma omp flush(flag1)
            
            IlPonte.search_titolo("Lord");
            IlPonte.search_titolo("The Ancient Mariner");

            IlPonte.presta(Commedia, Billy);
            
            IlPonte.biblio_info();
            #pragma omp flush
            #pragma omp atomic write
            flag2 = 1;
            #pragma omp flush(flag2)
        }
        #pragma omp section
        {
            while (1) {
                #pragma omp flush(flag1)
                #pragma omp atomic read
                temp_flag = flag1;
                if(temp_flag == 1) break;
            }
            IlPonte.add_book(Commedia);
            IlPonte.add_book(Shock);

            IlPonte.search_titolo("Lord");
            IlPonte.search_titolo("The Ancient Mariner");

            IlPonte.add_cliente(Engel);
             while (1) {
                #pragma omp flush(flag2)
                #pragma omp atomic read
                temp_flag = flag2;
                if(temp_flag == 1) break;
            }
            IlPonte.presta(Commedia, Engel);
            IlPonte.presta(Commedia, Giorgio);
           
            IlPonte.biblio_info();
        }
    }

}


