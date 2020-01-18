#include<bits/stdc++.h>
using namespace std;

std::atomic<bool> x,y;
std::atomic<int> z;

bool xx;

void write_x_then_y(){
    x.store(true, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);
    y.store(true, std::memory_order_relaxed); //当然也可以把y的存储改变内存序
}

//但是最大的意义在于用原子操作去操作非原子操作 p137
/* void write_x_then_y(){
    x = true; //如果不用屏障就不行了
    std::atomic_thread_fence(std::memory_order_release);
    y.store(true, std::memory_order_relaxed); //当然也可以把y的存储改变内存序
} */


void read_y_then_x(){
    while(!y.load(std::memory_order_relaxed))
        std::this_thread::yield();
    std::atomic_thread_fence(std::memory_order_acquire);
    if(x.load(std::memory_order_relaxed)){
        ++z;
    }
}

int main(){
    std::thread one(write_x_then_y);
    std::thread two(read_y_then_x);
    one.join();
    two.join();
    assert(z.load()!=0);
    std::atomic_flag flag;
    std::atomic<bool> fl;
    std::mutex mtx;
    mtx.lock();
    std::lock_guard<std::mutex> lk(mtx, std::adopt_lock);
    std:;unique_lock<std::mutex> lk()
    mtx.unlock();
    mtx.unlock();
    return 0;
}