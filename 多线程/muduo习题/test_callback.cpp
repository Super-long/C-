#include <bits/stdc++.h>
using namespace std;
#include "callback.h"

int test(int para){
    cout << "running in test : " << para << endl;
}

Signal<decltype(test)> pool;

void test_thread_connect(){
    auto x = pool.connect(test);
    getchar(); //延长x的时长
}

void test_thread_call(){
    pool.call(5);
}

std::shared_ptr<void> extend(new bool(false));
void test__(){
    auto x = pool.connect(test, extend);
}

int main(){
    vector<std::thread> vec(20);
    for(size_t i = 0; i < 20; i++){
        if(i == 1){
            vec[i] = std::thread(test__);
        }else if(i < 15 || i == 19)
            vec[i] = std::thread(test_thread_connect);
        else
            vec[i] = std::thread(test_thread_call); 
    }
    for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    return 0;
}