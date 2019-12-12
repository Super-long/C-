//http://www.cnblogs.com/haippy/p/3301408.html
//https://blog.csdn.net/yockie/article/details/8838686

//boost/thread/thread.hpp

#include<atomic> //其中有原子操作类型 编译器保证原子
#include<boost/thread/thread.hpp>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

atomic<int> al(0);

void click(){
    for(int i=0;i<100000;++i){
        al++;
    }
}

int main(){
    cout << "result : " << al << endl;
    std::thread a(click);
    a.detach(); 
    std::thread b(click);
    b.detach();     
    std::thread c(click);
    c.detach(); 
    /*
        a.join();
    b.join();
    c.join();*/
    //原子量中的操作表示这个操作使用的内存序
    getchar();
    cout << "result : " << al << endl;
    return 0;
}