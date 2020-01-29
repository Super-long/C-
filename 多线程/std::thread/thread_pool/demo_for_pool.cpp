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
    auto start = std::chrono::high_resolution_clock::now(); 
    for(size_t i = 0; i < 1000000; i++){
        vec[i] = pool.submit(&test);
    }
    for(size_t i = 0; i < 1000000; i++){
        vec[i].get(); //Can save expections well.
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::ratio<1,100000>> time_span 
    = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,100000>>>(end - start);

    cout << time_span.count() << endl;
    cout << "Count : "<< Count.load() << endl;
    return 0;
}