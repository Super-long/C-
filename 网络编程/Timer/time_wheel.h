#ifndef TIME_WHEEL_TIMER
#define TIME_WHEEL_TIMER

#include<time.h>
#include<iostream>
#include<cstdio>
#include<memory>
#include<vector>
#include<list>
#include<netinet/in.h>

//说实话　这个东西写的接口并不友好　客户类型得自己传一个迭代器
namespace Time_Wheel{
    const int BUFFER_SIZE = 64;
    class tw_timer;

    struct client_date{
        using itr = std::list<std::shared_ptr<tw_timer>>::iterator;
        struct sockaddr_in address;
        int socked;
        char buf[BUFFER_SIZE];
        //std::weak_ptr<tw_timer> ptr;//环状引用　说实话　第一次实际的遇到　希望记录一篇博客
        itr ptr; //值会多一次拷贝　后面写到这里的时候注意　再想想是否需要优化
        bool operator=(const client_date&) = delete; //不希望拷贝
        //设置这个的原因是让是客户可以O(1)找到自己的定时器　从而更新　说实话　时间堆还是不知道怎么改
    };

    class tw_timer{//定时器
        public:
            tw_timer(int rot,int ts):rotation(rot),time_solt(ts){}
        public:
            int rotation;//这个定时器还需要多少圈才生效
            int time_solt;//当前定时器所属于时间轮的槽数
            void (*cb_func)(std::shared_ptr<client_date>);
            std::shared_ptr<client_date> cd = nullptr;
    };

    class time_wheel{
        using itr = std::list<std::shared_ptr<tw_timer>>::iterator;
        public:
            time_wheel():vec(N),cur_slot(0){}
            itr add_timer(int timeout){//参数为超时时间
                if(timeout < 0){
                    throw std::exception();
                }
                std::size_t ticks = 0;
                if(timeout < SI){
                    ticks = 1;
                }else{
                    ticks = timeout / SI;
                }
                int rotation = timeout / N;//多少圈后被触发
                int ts = (cur_slot + (ticks % N)) %N;//所在槽
                auto timer = std::make_shared<tw_timer>(rotation,ts);
                vec[ts].emplace_back(timer);
                auto x = vec[ts].end();
                x--; 
                return x;//返回一个迭代器
            }
            void del_timer(itr tmp){ //传一个迭代器进来
                int ts = tmp->get()->time_solt;
                vec[ts].erase(tmp);
            }
            void tick(){
                auto first_node = vec[cur_slot].front();
                std::cout << "Current solt is " << cur_slot << std::endl;
                if(vec[cur_slot].empty()){
                    cur_slot = (cur_slot + 1) % N;
                    return;
                }
                for(auto x = vec[cur_slot].begin();!vec[cur_slot].empty() || x == vec[cur_slot].end();x++){
                    if(x->get()->rotation > 1){
                        x->get()->rotation -= 1;
                    }else{ //定时器已经到期
                        x->get()->cb_func(x->get()->cd); //执行回调函数
                        vec[cur_slot].erase(x);
                    }   
                }
                cur_slot = (cur_slot + 1) % N;
            }
        private:
            enum{SI = 2,N = 60};//N为时间轮槽数　SI为一个心博时间　SI应该与信号发送间隔相同
            std::vector<std::list<std::shared_ptr<tw_timer>>>vec;
            int cur_slot; //当前时间槽
    };
}

#endif