#include <iostream>
#include <omp.h>
#include "trains.h"
#include<ctime>
#include<cmath>

using namespace std;

//0 vagone merci, 1 vagone passeggeri

int main(){

    // piccolo test di creazione vagoni e treni
    Vagone vm(0);
    Treno t(111, "Borgo","Trento");
    t.add_vagone(vm);
    vm.info_vagone();
    Vagone vp(1);
    t.add_vagone(vp);
    vp.info_vagone();
    t.info_treno();
    


    // creazione dei 10 treni di vagoni di numero randomico
    vector<Treno> treni; //conterrà i treni creati


    bool binari[2]={0,0}; //0 significa che è occupato se 1 significa che è libero

    bool flag[10];//flag per la creazione 10 treni;
    for(int i=0;i<10;i++){
        flag[i]=0;
    }
    bool flag2[10];//flag per assicurarmi che il treno sia passato in stazione, 0 se deve passsare, 1 se è passato
    for(int i=0;i<10;i++){
        flag2[i]=0;
    }

    #pragma omp parallel sections shared(treni)
    {   
        #pragma omp section
        { //sezione che costruisce i treni e li invia alla stazione di arrivo
            for(int j=0; j<10; j++){

                string s(1,char(j+65));
                Treno t(j,s, "Trento");
                treni.push_back(t);
                srand((int)time(NULL));
                for(int i=0; i<5; i++) rand();//per avere i numeri più diversi tra loro tra un esecuzione e l'altra
                int vagoni_merci=round(static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/5)));
                int vagoni_passeggeri=round(static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/5)));
                for(int i=0; i<vagoni_merci; i++){
                    Vagone v_merci(0);
                    treni[j].add_vagone_copia(v_merci);
                } 
                for(int i=0; i<vagoni_passeggeri; i++){
                    Vagone v_passeggeri(1);
                    treni[j].add_vagone_copia(v_passeggeri);
                }
                std::cout<<endl<<j<<endl;
                treni[j].info_treno2();
                #pragma omp flush
                #pragma omp atomic write
                flag[j]=1; //il treno è pronto
                #pragma omp flush(flag)
            }
        }
        
        /*#pragma omp section 
        {//binario 1 
            int a=0;
            
            while(1){
                int j=a%treni.size(); //ad ogni ciclo controlla un treno diverso
                while (1) {
                    #pragma omp flush(flag)
                    #pragma omp atomic read
                    bool temp_flag = binari[0];
                    if(temp_flag == 1) break;
                }
            
                #pragma omp flush
                #pragma omp atomic write
                binari[0] = 1;
                #pragma omp flush(binari)
                std::cout<<"Treno "<<treni[j].show_ID()<<" entrato in stazone binario 1";

                #pragma omp flush
                #pragma omp atomic write
                binari[0] = 1;
                #pragma omp flush(binari)
                flag2[j]=1;
                std::cout<<"Treno "<<treni[j].show_ID()<<" uscito dalla stazone binario 1";
                

                int count=0;
                for(int i=0;i<10; i++){
                    count+=flag2[i];
                }
                if(count==10) break; //se questo è vero tutti i treni sono passati e usciti dalla stazione e il programma può concudersi
                a++;
            }
            
        }

        #pragma omp section 
        {//binario 2 
            int a=0;
            while(1){
                int j=a%treni.size();
                while (1) {
                    #pragma omp flush(flag)
                    #pragma omp atomic read
                    bool temp_flag = binari[1];
                    if(temp_flag == 1) break;
                }
            
                cout<<"Treno "<<treni[j].show_ID()<<" entrato in stazone binario 2";
                cout<<"Treno "<<treni[j].show_ID()<<" uscito dalla stazone binario 2";
                flag2[j]=1;

                #pragma omp flush
                #pragma omp atomic write
                binari[1] = 1;
                #pragma omp flush(flag)

                int count=0;
                for(int i=0;i<10; i++){
                        count+=flag2[i];
                }
                if(count==10) break; //se questo è vero tutti i treni sono passati e usciti dalla stazione e il programma può concudersi           
            }
            
        }*/
        //mancherebbe la sezione che appena il trenoo è creato riordina l'array di treni in ordine di attesa come richiesto
        
    }
}