//test per generare numeri random

#include <iostream>
#include <ctime>
using namespace std;
int main(){
    srand((int)time(NULL));
    for (int i=0;i<5;i++) {
        for (int j = 0; j < 5; j++) {
            cout <<  static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20))) << " ";
        }
        cout << '\n';
    }
}