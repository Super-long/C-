#ifndef MANGER_H_
#define MANGER_H_

#include"../base/copyable.h"
#include"socket.h"
#include"../net/epoll.h"
#include<unordered_map>
#include<memory>
#include"../tool/member.h"

namespace ws{
    class Manger : public Copyable{
        public:
            explicit Manger(Epoll& _epoll) : _Epoll_(_epoll){}
            


        private:
            Epoll& _Epoll_;
            std::unordered_map<int,std::unique_ptr<Member>> Fd_To_Member;
    };
}



#endif