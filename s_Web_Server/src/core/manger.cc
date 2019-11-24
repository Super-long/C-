#include"manger.h"
#include"../net/epoll_event.h"
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
        //if()//判断解析出来是否存在keepalive       
    }

    void Manger::Reading(int fd, int time){
        if(!Exist(fd)){
            throw std::invalid_argument("'Manger::Reading' Don't have this fd.");
        }
        auto& user = Fd_To_Member[fd];
        
    } 

    void Manger::Writing(int fd, int time){

    }
}