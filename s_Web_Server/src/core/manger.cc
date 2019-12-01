#include"manger.h"
#include"../net/epoll_event.h"
#include<iostream>
namespace ws{
    int Manger::Opera_Member(std::unique_ptr<Member>& ptr,EpollEventType& EE){
        int id = ptr->fd();         //RTTI
        Fd_To_Member.emplace(id,ptr.release());
        _Epoll_.Add(*Fd_To_Member[id],EE); 
        return id;      
    }

    int Manger::Opera_Member(std::unique_ptr<Member>&& ptr,EpollEventType&& EE){
        int id = ptr->fd();         
        Fd_To_Member.emplace(id,ptr.release());
        _Epoll_.Add(*Fd_To_Member[id],EE); 
        return id;      
    }

    int Manger::Opera_Member(std::unique_ptr<Member>&& ptr,EpollEventType& EE){
        int id = ptr->fd();         
        Fd_To_Member.emplace(id,ptr.release());
        _Epoll_.Add(*Fd_To_Member[id],EE); 
        return id;      
    }

    int Manger::Opera_Member(std::unique_ptr<Member>& ptr,EpollEventType&& EE){
        int id = ptr->fd();         
        Fd_To_Member.emplace(id,ptr.release());
        _Epoll_.Add(*Fd_To_Member[id],EE); 
        return id;      
    }

    int Manger::Remove(int fd){
        if(!Exist(fd)){
            throw std::invalid_argument("'Manger::Remove' Don't have this fd.");
        }
        _Epoll_.Remove(*Fd_To_Member[fd],EpollTypeBase());
        Fd_To_Member.erase(fd);
    }

    int Manger::Update(int fd){
        if(!Exist(fd)){
            throw std::invalid_argument("'Manger::Update' Don't have this fd.");
        }
        _Epoll_.Modify(*Fd_To_Member[fd],EpollTypeBase());
    }

    int Manger::JudgeToClose(int fd){
        if(!Exist(fd)){
            throw std::invalid_argument("'Manger::JudgeToClose' Don't have this fd.");
        }
        auto& T = Fd_To_Member[fd];

        if(T->CloseAble()){
            _Epoll_.Remove(static_cast<EpollEvent>(fd));
            auto temp = Fd_To_Member.find(fd);
            Fd_To_Member.erase(temp);
        }
    }

    void Manger::Reading(int fd, long _time_){
        if(!Exist(fd)){
            throw std::invalid_argument("'Manger::Reading' Don't have this fd.");
        }
        auto& user = Fd_To_Member[fd];//得到相关连接的信息
        user->DoRead();
        
        user->Touch(_time_);
    } 
 
    void Manger::Writing(int fd, long time){

    }
}