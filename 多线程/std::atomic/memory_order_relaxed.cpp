#include<bits/stdc++.h>
using namespace std;

std::atomic<int> x(0),y(0),z(0);
std::atomic<bool> go(false);

unsigned const loop_count = 10;

struct read_value{
    int x,y,z;
};

read_value value1[loop_count];
read_value value2[loop_count];
read_value value3[loop_count];
read_value value4[loop_count];
read_value value5[loop_count];

void increment(std::atomic<int>* var, read_value* value){
    while(!go) //自旋 等待所有线程同时开始
        std::this_thread::yield();
    for(unsigned i=0;i<loop_count;++i){
        value[i].x = x.load(std::memory_order_relaxed);
        value[i].y = y.load(std::memory_order_relaxed);
        value[i].z = z.load(std::memory_order_relaxed);
        var->store(i+1, std::memory_order_relaxed);
        std::this_thread::yield();
    }
}

void read_vals(read_value* value){
    while(!go)
        std::this_thread::yield();
    for(unsigned i=0;i<loop_count;++i){
        value[i].x = x.load(std::memory_order_relaxed);
        value[i].y = y.load(std::memory_order_relaxed);
        value[i].z = z.load(std::memory_order_relaxed);
        std::this_thread::yield();
    }  
}

void print(read_value* v){
    for(size_t i = 0; i < loop_count; i++){
        if(i) cout << ',';
        std::cout << "("<<v[i].x <<"," << v[i].y <<"," <<v[i].z << ")";
    }
    std::cout << endl;
}

int main(){
    std::thread t1(increment,&x,value1);
    std::thread t2(increment,&y,value2);
    std::thread t3(increment,&z,value3);
    std::thread t4(read_vals,value4);
    std::thread t5(read_vals,value5);
    go = true;
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    print(value1);
    print(value2);
    print(value3);
    print(value4);
    print(value5);
    return 0;
}