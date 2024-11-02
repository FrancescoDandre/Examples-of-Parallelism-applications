#include <iostream>
#include "ditta.h"
using namespace std;
#include <omp.h>

int main(){
    //Product casco("casco white",100,1);
    //Product occhiali("pro glasses",30,0.5);
    Magazzino Centrale("Trento", 1000);
    Centrale.fill("casco", 400);
    Centrale.fill("occhiali",200);
    Centrale.fill("bici",300);
    Centrale.info();
    Centrale.fill("bici",50);
    Centrale.fill("pedali", 100);
    Centrale.info();

    Magazzino TheSecond("Bassano", 450);
    Magazzino TheCapitol("Roma", 679);
    Delivery_Company DandreComp;
    DandreComp.add_magazzino(Centrale);
    DandreComp.add_magazzino(TheSecond);
    DandreComp.add_magazzino(TheCapitol);

    Ordine uno=newOrder("casco",3,"Bassano",1);
    Ordine due=newOrder("casco", 2, "Roma", 2);
    DandreComp.Order(uno);
    DandreComp.Order(due);
    DandreComp.seeOrders();

    Route r1=DandreComp.planRoute("Trento", "Bassano",TheSecond, 40, uno);
    Camion c1(10, 80);
    int t[3];
    DandreComp.timeForecast(r1, c1, t);
    cout<<"tempo previsto in minuti (totale, in viaggio, fermi)"<<endl;
    cout<<t[0]<<" "<<t[1]<<" "<<t[2]<<endl;
    c1.info();
    c1.fill("casco", 11);
    c1.fill("bici", 1);
    c1.info();
    DandreComp.add_camion(c1);
    DandreComp.execute(r1, c1, t);
    cout<<"tempo effettivo in minuti (totale, in viaggio, fermi)"<<endl;
    cout<<t[0]<<" "<<t[1]<<" "<<t[2]<<endl;
    c1.info();
    TheSecond.info();

    Route r2=DandreComp.planRoute("Trento", "Roma",TheCapitol, 570, due);
    Camion c2(50, 85);
    DandreComp.timeForecast(r2, c2, t);
    cout<<"tempo previsto in minuti (totale, in viaggio, fermi)"<<endl;
    cout<<t[0]<<" "<<t[1]<<" "<<t[2]<<endl;
    DandreComp.add_camion(c2);
    c2.fill("casco",3);
    DandreComp.execute(r2,c2,t);
    cout<<"tempo effettivo in minuti (totale, in viaggio, fermi)"<<endl;
    cout<<t[0]<<" "<<t[1]<<" "<<t[2]<<endl;
    TheCapitol.info();

    DandreComp.seeOrders();
    
    
    //sezione parallela
    Ordine OrdersArr[100];
    Magazzino MagazziniArr[100];
    Camion CamionArr[100];
    Route RouteArr[100];
    int flag[100];
    for(int i=0;i<100;i++){
        flag[i]=0;
    }
    int temp_flag;
    #pragma omp parallel sections
    {
        #pragma omp section
        { //producer
            //produce data
            for(int i=65; i<91; i++){
                string s(1, char(i));//prodotto
                string f(1, char(i+32));//città arrivo
                OrdersArr[i-65]=newOrder(s,i,f,2);
                DandreComp.Order(OrdersArr[i-65]);
                Magazzino m(f,i*10);
                MagazziniArr[i-65]=m;
                DandreComp.add_magazzino(MagazziniArr[i-65]);
                Camion c(i,i-i*0.1);
                CamionArr[i-65]= c;
                DandreComp.add_camion(CamionArr[i-65]);
                CamionArr[i-65].fill(s,i);
                Route r=DandreComp.planRoute("trento",f,MagazziniArr[i-65],i,OrdersArr[i-65]);
                RouteArr[i-65]=r;
                #pragma omp flush
                #pragma omp atomic write
                flag[i-65]=1;
                #pragma omp flush(flag)
                cout<<"ordine "<<i-65<<" pronto"<<endl;
            }
            //DandreComp.seeOrders();
        }
        #pragma omp section
        {//consumer
            for(int i=65; i<91; i++){
                while (1) {
                    #pragma omp flush(flag)
                    #pragma omp atomic read
                    temp_flag = flag[i-65];
                    if(temp_flag == 1) break;
                }
                //use data
                DandreComp.timeForecast(RouteArr[i-65], CamionArr[i-65], t);
                cout<<"tempo previsto in minuti (totale, in viaggio, fermi) "<<i-65<<endl;
                cout<<t[0]<<" "<<t[1]<<" "<<t[2]<<endl;
                DandreComp.execute(RouteArr[i-65], CamionArr[i-65], t);
                cout<<"tempo effettivo in minuti (totale, in viaggio, fermi) "<<i-65<<endl;
                cout<<t[0]<<" "<<t[1]<<" "<<t[2]<<endl;
                cout<<"ordine "<<i-65<<" completato"<<endl;
            }
        }
    }
    DandreComp.seeOrders();
}