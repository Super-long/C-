// 为了处理项目中一个内存泄漏的问题，即一个thread_local变量的内存泄露
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void Delete_(int* para){
    if(para == nullptr) return;
    cout << "nihao\n";
    delete para;
    return;
}
thread_local int* env = nullptr;

thread_local std::unique_ptr<int, decltype(Delete_)*>
    Env(env, Delete_);

void* Routine(void* para){
    Env.reset();
    env = new int(5);
    Env.reset(env);
    cout << "函数结束\n";
    return 0;
}

int main(){
    pthread_t tid[5];
    for(size_t i = 0; i < 2; i++){
        pthread_create(tid + i, nullptr, Routine, 0);
    }
    for(size_t i = 0; i < 2; i++){
        pthread_join(tid[i], nullptr);
    }
    sleep(1);
    return 0;
}