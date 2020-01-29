#include <bits/stdc++.h>
using namespace std;
#include "Thread_pool_2.h"


/**
 * 这种线程池思路固然好 但是实际作用不大 除非每个线程都有push的权利 实际都在pool中
 * @ 每个线程干自己的事情才是效率最高的
*/

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