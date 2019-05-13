#include <iostream>
#include "skip.h"
#include "skip.cpp"
#include <string>
#include <ctime>

using namespace std;

// clang++ -Wall -Wextra -g mainskip.cpp skip.cpp -o mainskip

int main(){
    clock_t start, finish;
    double tm;
    int n, v;
    string op;
    skip<int>* s = new skip<int>();
    cout << "Insert operation and sequence size:" << endl;
    cin >> op >> n;
    while(op.compare("end")){
        start=clock();
        for (int i = 0; i < n; i++){
            cin >> v;
            if(!op.compare("s"))
                if(s->search(v))
                    cout << v << " true" << endl;
                else
                    cout << v << " false" << endl;
            else if(!op.compare("i"))
                s->insert(v);
            else if(!op.compare("r"))
                s->remove(v);
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
            cout << "MAX: " << s->max() << endl;
            finish = clock();
            tm = 1000.0 * (finish - start) / CLOCKS_PER_SEC; 
            cout << "Max time: " << tm << endl;
        }
        if(!op.compare("min")) {
            start = clock();
            cout << "MIN: " << s->min() << endl;
            finish = clock();
            tm = 1000.0 * (finish - start) / CLOCKS_PER_SEC; 
            cout << "Min time: " << tm << endl;
        }
        s->printSkip();
        cout << "Insert operation and sequence size:" << endl;
        cin >> op >> n;
    }
    
    return 0;
}