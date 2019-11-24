#ifndef MANGER_H_
#define MANGER_H_

#include"../base/copyable.h"
#include"socket.h"
#include"../net/epoll.h"
#include<unordered_map>
#include<memory>
#include"../tool/member.h"
#include"../net/epoll_event.h"

namespace ws{
    class Manger : public Copyable{
        public:
            explicit Manger(Epoll& _epoll) : _Epoll_(_epoll){}
            int Opera_Member(std::unique_ptr<Member>&, EpollEventType&);
            int Opera_Member(std::unique_ptr<Member>&&, EpollEventType&&);
            int Opera_Member(std::unique_ptr<Member>&, EpollEventType&&);
            int Opera_Member(std::unique_ptr<Member>&&, EpollEventType&);

            void TimeWheel();//定时器 后来再实现  

            void Reading(int fd, int time);
            void Writing(int fd, int time);
            int JudgeToClose(int fd);
            int Update(int fd);

            int Remove(int fd);
            bool Exist(int fd){if(Fd_To_Member.find(fd) != Fd_To_Member.end()) return true; return false;}

        private:
            Epoll& _Epoll_;
            std::unordered_map<int,std::unique_ptr<Member>> Fd_To_Member;
    };
}



#endif