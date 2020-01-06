//
// Created by lizhaolong on 2020/1/6.
//

#include<bits/stdc++.h>
using namespace std;

void work(){
    cout << "one loop\n";
}

std::thread f(){
    std::thread t(work);
    std::cout << t.get_id() << std::endl;
    return t;
}

int main(){
    vector<std::thread> threads;
    std::thread T = f();
    std::cout << T.get_id() << std::endl;
    T.join();
    for(int i=0;i<10;++i){
        threads.emplace_back(thread(work));
    }
    //std::mem_fn相当于给每个容器内的对象执行一个成员函数 bind也可以做到且更为通用
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    cout << std::thread::hardware_concurrency() << endl;
    return 0;
}