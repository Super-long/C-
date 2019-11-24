#include<iostream>
//#include<co_routine.h>
#include"../../libco/co_routine.h"
#include<vector>
using namespace std;

struct node{
    stCoCond_t* cond;
    std::vector<int> vecData;
    int id;//数据id
    int cid;//协程id
};

void* producer(void* args){
    co_enable_hook_sys(); //启动协程
    node* p = static_cast<node*>(args);
    int cid = ++p->cid;
    int counter = 0;
    while(true){
        ++counter;
        for(int i = 0; i < 5 ;++i){
            p->vecData.push_back(counter);
            cout << cid << " + add new data!";
        }
        co_cond_signal(p->cond);
    }
    return nullptr;
}

void* Consumer(void* args){
    co_enable_hook_sys(); //启动协程HOOK项
    node* p = static_cast<node*>(args);
    int cid = ++p->cid;
    while(true){
        if(p->vecData.empty()){
            co_cond_timedwait(p->cond, -1);
            continue;
        }
        std::cout << cid << " -del data " << p->vecData.front() << std::endl;
        p->vecData.erase(p->vecData.begin());
    }
    return nullptr;
}

int main(){
    stCoRoutine_t* Pro = nullptr;
    stCoRoutine_t* Con[5] = { nullptr};
    
    node Temp;
    Temp.cid = Temp.id = 0;
    Temp.cond = co_cond_alloc();
    
    co_create(&Pro, nullptr, producer, &Temp); //创建生产者协程 
    co_resume(Pro);//启动协程
    std::cout << "start productor create sucess.\n";
    for(int i = 0; i < 5; ++i){
        co_create(&Con[i], nullptr, Consumer, &Temp);
        co_resume(Con[i]);
    }
    std::cout << "start consumer coroutine sucess.\n";
    co_eventloop(co_get_epoll_ct(), nullptr, nullptr);
    return 0;
}