#include<bits/stdc++.h>
using namespace std;

int sum_a __attribute__ ((aligned(64)));
//int sum_b __attribute__ ((aligned(64)));

void fun_aaaaaaaaaaaaaaaaaaaa(){
    sum_a++;
        std::atomic_thread_fence(std::memory_order_seq_cst);
    return;
}

int main(){
    auto tha = thread(fun_aaaaaaaaaaaaaaaaaaaa);
    auto thb = thread(fun_aaaaaaaaaaaaaaaaaaaa);
    
    tha.join();
    thb.join();
    return 0;
}