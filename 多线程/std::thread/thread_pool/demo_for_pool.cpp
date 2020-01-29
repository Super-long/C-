#include <bits/stdc++.h>
using namespace std;
#include "Thread_pool.h"

atomic<int> Count(0);

int test(){
    ++Count;
    return 10;
}

int main(){
    thread_pool pool;
    vector<future<int>> vec(1000000);
    for(size_t i = 0; i < 1000000; i++){
        vec[i] = pool.submit(&test);
    }
    for(size_t i = 0; i < 1000000; i++){
        vec[i].get(); //可以很好的保存异常
    }    
    cout << "Count : "<< Count.load() << endl;
    return 0;
}