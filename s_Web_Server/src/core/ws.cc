#include"../base/Y_Dragon.h"
#include<signal.h>
#include<iostream>
#include<assert.h> 
#include<sys/time.h>
#include"ws.h"
#include<errno.h>

namespace ws{

    int64_t Get_Current_Time(){
        timeval now;
        int ret = gettimeofday(&now, nullptr);
        assert(ret != 1);
        return now.tv_sec*1000 + now.tv_usec / 1000;
    }

    Web_Server::Web_Server() : _Epoll_(), _Manger_(_Epoll_), _Server_(Y_Dragon::MyPort()){}

    void Web_Server::Running(){ 
        try{
            signal(SIGPIPE, SIG_IGN);
            _Server_.Set_AddrRUseP();
            _Server_.Server_BindAndListen();
            _Epoll_.Add(_Server_, EpollCanRead());
            EpollEvent_Result Event_Reault(Y_Dragon::EventResult_Number());

            while(true){
                //constexpr int Second = 20;
                _Epoll_.Epoll_Wait(Event_Reault);
                for(int i = 0; i < Event_Reault.size(); ++i){
                    auto & item = Event_Reault[i];
                    int id = item.Return_fd();

                    if(id == _Server_.fd()){//正常
                        _Server_.Server_Accept([this](int fd){_Manger_.Opera_Member(std::make_unique<Member>(fd),EpollCanRead());});
                        _Epoll_.Modify(_Server_, EpollCanRead());
                    }else if(item.check(EETRDHUP)){
                        _Manger_.Remove(id); //正常
                    }else if(item.check(EETCOULDREAD)){
                        _Manger_.Reading(id);
                        _Manger_.Update(id); //这里没有考虑完全错误的报文
                    } 
                }
                //TODO :调用时间轮
            }
        } catch (std::exception& err){
            std::cout << err.what() << std::endl;
        }
    }
}