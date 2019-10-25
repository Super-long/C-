#ifndef LST_TIMER
#define LST_TIMER

#include<iostream>
#include<queue>
#include<algorithm>
#include<time.h>
#include<memory>
#include<sys/types.h>
#include<sys/socket.h>

//正常的写法是链表　复杂度为N 希望优化
//一个失败的写法　堆没有办法调整任务时间　致命错误　没动脑子就动手　这就是下场

namespace LIST_TIMER{
    const int BUFFER_SIZE = 64;
    class util_timer;

    struct client_data{//客户信息类
        //struct sockaddr_in address; //C++中好像没有这个

        int sockfd;
        char buf[BUFFER_SIZE];
        //util_timer *timer;
        std::shared_ptr<util_timer>timer;
    };

    class util_timer{//定时器类
        public:
            util_timer();
        public:
            time_t expire;//超时时间
            void (*cb_func) (std::shared_ptr<client_data>&);//一个函数指针　可注册回调函数
            std::shared_ptr<client_data> data;
    };

    class timer_heap
    {
    public:
        timer_heap():que(){}
        ~timer_heap(){
            while(!que.empty()){
                que.pop();
            }
        }
        void push(util_timer* tmp){ //留给外界的接口是一个指针　接口并不友好
            que.push(pot(tmp));
        }
        void tick(){
            time_t cur = time(nullptr);
            while(!que.empty()){
                auto x = que.top();
                if(cur < x.ptr->expire) break;
                x.ptr->cb_func(x.ptr->data);//执行回调函数
                que.pop();
            }
        }
    private:
        class pot{
            public:
                explicit pot(util_timer *T):ptr(T){}
                bool operator<(pot &a)const{
                    return ptr->expire < a.ptr->expire;
                }
            public:
                std::shared_ptr<util_timer> ptr; 
        };
        std::priority_queue<pot> que;
    };
    
};

#endif 