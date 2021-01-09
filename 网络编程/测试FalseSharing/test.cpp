#include <bits/stdc++.h>
#include <thread>
using namespace std;

bool SetCPUaffinity(int param){  //arg  传递线程标号（自己定义）
    cpu_set_t mask;         // CPU核的集合

    CPU_ZERO(&mask);        // 置空
    CPU_SET(param,&mask);   // 设置亲和力值,把cpu加到集合中 https://man7.org/linux/man-pages/man3/CPU_SET.3.html
    // 第一个参数为零的时候默认为调用线程
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1){   // 设置线程CPU亲和力
        return false;
        // 看起来五种errno没有必要处理；
    } else {
        return true;   
    }
}

/* int num0 __attribute__ ((aligned(64)));
int num1 __attribute__ ((aligned(64))); */

int num0;
char arr[60];
int num1;

void thread0(int index){
    SetCPUaffinity(index);
    int count = 100000000;  // 10亿
    while(count--){
        num0++;
    }
    return;
}

void thread1(int index){
    SetCPUaffinity(index);
    int count = 100000000;
    while(count--){
        num1++;
    }
    return;
}

int main(){
    vector<std::thread> pools;
    pools.emplace_back(thread(thread0, 0));
    //pools[0].join();
    pools.emplace_back(thread(thread1, 1));
    //pools[1].join();
    for_each(pools.begin(), pools.end(), std::mem_fn(&std::thread::join));
    return 0;
}