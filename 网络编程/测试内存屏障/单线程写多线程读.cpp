#include<bits/stdc++.h>
using namespace std;

int data[15] __attribute__ ((aligned(64)));

void func_write(){
    int count = 100000;
    while(count--){
        for(int i = 0; i < 15; ++i){
            int& x = data[i];
            if(count&1){
                x = 1111111;
            } else {
                x = 2222222;
            }
        }
        std::atomic_thread_fence(memory_order_release);
        std::this_thread::yield();
    }
}

void func_read(){
    int count = 100000;
    int prev = 0;
    while(count--){
        std::atomic_thread_fence(memory_order_acquire);
        for(int i = 0; i < 15; ++i){
            if(0 == i){
                prev = data[i];
            } else {
                if(prev != data[i]){
                    // 如果出现这种情况就证明出现了
                    cout << "error : " << prev << " -> " << data[i] << endl;
                    exit(1);
                }
            }
        }
    }
}

int main(){
    auto wri = std::thread(func_write); 
    auto rea1 = std::thread(func_read); 
    auto rea2 = std::thread(func_read); 

    wri.join();
    rea1.join();
    rea2.join();

    return 0;
}