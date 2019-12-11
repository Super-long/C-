/* #include<atomic>
#include<thread>
#include<iostream>
#include<assert.h>
using namespace std;

std::atomic<bool>x,y;
std::atomic<int>z;

void write_x(){
    x.store(true, std::memory_order_relaxed);
}

void write_y(){
    y.store(true, std::memory_order_relaxed);
}


void read_x_then_y(){
    while(!x.load(std::memory_order_relaxed));
    if(y.load(std::memory_order_relaxed)) ++z;
}

void read_y_then_x(){
    while(!y.load(std::memory_order_relaxed));
    if(x.load(std::memory_order_relaxed)) ++z;
}

int main(){
    x = false; y = false;
    z = 0;
    std::thread a(write_x); a.detach();
    std::thread b(write_y); b.detach();
    std::thread c(read_x_then_y); c.detach();
    std::thread d(read_y_then_x); d.detach();
    cout << z.load() << endl;
    assert(z.load() != 0);
    return 0;
}
 */

//内存序用于控制变量在不同线程的顺序可见性问题
//即线程中的指令可能被重排
#include <atomic>
#include <iostream>
#include <thread>
#include <assert.h>
using namespace std;

std::atomic<bool> x,y;
std::atomic<int> z;
 
void write_x()
{
    x.store(true,std::memory_order_relaxed);//默认参数:memory_order_seq_cst
}
 
 
 
void write_y()
{
    y.store(true,std::memory_order_relaxed);  
}
 
 
 
void read_x_then_y()
{
    while(!x.load(std::memory_order_relaxed));
 
    if(y.load(std::memory_order_relaxed))      
 
        ++z;
}
 
 
 
void read_y_then_x()
{
    while(!y.load(std::memory_order_relaxed));
 
    if(x.load(std::memory_order_relaxed))    
 
        ++z;
}
 
 
 
int main()
{
 
    x=false;
 
    y=false;
 
    z=0;
 
    std::thread a(write_x);
 
    std::thread b(write_y);
 
    std::thread c(read_x_then_y);
 
    std::thread d(read_y_then_x);
 
    a.join();
 
    b.join();
 
    c.join();
 
    d.join();

    cout << z.load() << endl;
    assert(z.load()!=0);                  
 
}
