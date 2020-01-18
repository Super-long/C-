#include<bits/stdc++.h>
using namespace std;

std::atomic<int> Data[5];
std::atomic<bool> sync1(false), sync2(false);
std::atomic<int> sync(false);

void thread_1(){
    Data[0].store(42, std::memory_order_relaxed);
    Data[1].store(42, std::memory_order_relaxed);
    Data[2].store(42, std::memory_order_relaxed);
    Data[3].store(42, std::memory_order_relaxed);
    Data[4].store(42, std::memory_order_relaxed);
//    sync1.store(true, std::memory_order_release);
    sync.store(true, std::memory_order_release);
}

//happens_before的传递关系
void thread_2(){
    while(!sync1.load(std::memory_order_acquire)); //自旋
    sync2.store(true, std::memory_order_release);
}
//与上面的写法差不多
void Merge(){
    int expected = 1;
    while(sync.compare_exchange_strong(expected, 2, std::memory_order_acq_rel));
}

void thread_3(){
    //while(!sync2.load(std::memory_order_acquire));
    while(!sync.load(std::memory_order_acquire));
    assert(Data[0] == 42);
    assert(Data[1] == 42);
    assert(Data[2] == 42);
    assert(Data[3] == 42);
    assert(Data[4] == 42);
}

int main(){
    std::thread a(thread_1);
    std::thread b(Merge);
    std::thread c(thread_3);
    a.join();
    b.join();
    c.join();
    return 0;
}