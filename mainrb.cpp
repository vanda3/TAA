#include <iostream>
#include "rb.h"
#include "rb.cpp"
#include <string>
#include <ctime>

using namespace std;

// clang++ -Wall -Wextra -std=c++11 -g mainrb.cpp rb.cpp -o mainrb

int main(){
    clock_t start, finish;
    double tm;
    int count=0;
    int n, v;
    string op;
    rb<int>* r = new rb<int>();
    cout << "Insert operation and sequence size:" << endl;
    cin >> op >> n;
    while(op.compare("end")){
        start=clock();
        for (int i = 0; i < n; i++){
            cin >> v;
            if(!op.compare("s"))
                if(r->search(v))
                    cout << v << " true" << endl;
                else
                    cout << v << " false" << endl;
            else if(!op.compare("i")){
                r->insert(v);
                count+=n;
            }
            else if(!op.compare("r")){
                r->remove(v);
            }
            else
                continue;
        }
        finish=clock();
        tm = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
        if(!op.compare("s")) cout << "Search time: " << tm << endl;
        else if(!op.compare("i")) cout << "Insert time: " << tm << endl;
        else if(!op.compare("r")) cout << "Remove time: " << tm << endl;
        if(!op.compare("max")) {
            start = clock();
            cout << "MAX: " << r->max() << endl;
            finish = clock();
            tm = 1000.0 * (finish - start) / CLOCKS_PER_SEC; 
            cout << "Max time: " << tm << endl;
        }
        if(!op.compare("min")) {
            start = clock();
            cout << "MIN: " << r->min() << endl;
            finish = clock();
            tm = 1000.0 * (finish - start) / CLOCKS_PER_SEC; 
            cout << "Min time: " << tm << endl;
        }
        r->printRB(count);
        if(op!="end"){
            cout << "Insert operation and sequence size:" << endl;
            cin >> op >> n;
        }
    }
    
    return 0;
}