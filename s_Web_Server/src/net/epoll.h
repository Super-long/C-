#ifndef WEBSERVER_EPOLL
#define WEBSERVER_EPOLL

#include<sys/epoll.h>
#include"epoll_event_result.h"
#include"../base/nocopy.h"
#include"../base/havefd.h"

namespace ws{
    class Epoll final : public Nocopy,Havefd{
        public:
            Epoll() : epoll_fd_(epoll_create1(::EPOLL_CLOEXEC)) {}
            void Epoll_Wait(EpollEvent_Result& ETT){
                Epoll_Wait(ETT,-1);
            }
            void Epoll_Wait(EpollEvent_Result& ETT,int timeout){
                int Available_Event_Number_ =                           //可以逐字节转化的原因是类中无其他元素
                    epoll_wait(epoll_fd_,reinterpret_cast<epoll_event*>(ETT.array.get()),ETT.All_length,timeout);
                ETT.Available_length = Available_Event_Number_;
            }
            int fd() const override{return epoll_fd_; }
            
            int Add(EpollEvent& para){
                epoll_ctl(epoll_fd_, EPOLL_CTL_ADD,para.Return_fd(),para.Return_Pointer());
            }
            int Add(EpollEvent&& para){//考虑这个到底有没有意义
                epoll_ctl(epoll_fd_, EPOLL_CTL_ADD,para.Return_fd(),para.Return_Pointer());
            }

        private:
            int epoll_fd_;
    };
}

#endif