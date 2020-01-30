#include<bits/stdc++.h>
using namespace std;
#include "skiplist.h"

int main(){
    shared_ptr<int[]> book(new int[16]);
    book[5] = 5;

    SkipList<int> sl;
    for(size_t i = 1; i <= 5; i++)
    {
        sl.insert(i);
    }
    for(size_t i = 1; i <= 5; i++)
    {
        cout << sl.find(i).value << endl;
    }

    for(size_t i = 1; i <= 5; i+=2){
        sl.Delete(i);
    }

    sl.show();  
}