#include<atomic>
#include<thread>
#include<iostream>
#include<assert.h>
using namespace std;

std::atomic<bool>x,y;
std::atomic<int>z;

void write_x(){
    //x.store(true, std::memory_order_relaxed);
    cout << "-zero\n";
    cout << "-one\n";
    cout << "-two\n";
    //y.store(true, std::memory_order_relaxed);
    cout << "-three\n";
    cout << "-four\n";
    cout << "-five\n";
}

void write_y(){
    
    cout << "zero\n";
    cout << "one\n";
    cout << "two\n";
    //y.store(true, std::memory_order_relaxed);
    cout << "three\n";
    cout << "four\n";
    cout << "five\n";
}


void read_x_then_y(){
    //while(!x.load(std::memory_order_relaxed));
    //if(y.load(std::memory_order_relaxed)) ++z;
}

void read_y_then_x(){
    //while(!y.load(std::memory_order_relaxed));
    //if(x.load(std::memory_order_relaxed)) ++z;
}

int main(){
    x = false; y = false;
    z = 0;
    std::thread a(write_x);
    std::thread b(write_y);
    a.join(); b.join();
    getchar();
    //std::thread c(read_x_then_y); c.detach();
    //std::thread d(read_y_then_x); d.detach();
    //cout << z.load() << endl;
    //assert(z.load() != 0);
    return 0;
}