#include"socket.h"
#include<errno.h>
#include<iostream>
namespace ws{
    int Socket::Close(){
        int rv = ::close(Socket_fd_);
        if(rv != -1) Have_Close_ = false;
        return rv;
    }

    int Socket::SetNoblocking(int flag){
        int old_option = fcntl(Socket_fd_,F_GETFL);
        int new_option = old_option | O_NONBLOCK | flag;
        fcntl(Socket_fd_,F_SETFL,new_option);
        return old_option;
    } 

    int Socket::Read(std::shared_ptr<UserBuffer> ptr, int length, int flag){
        if(length == -1 || length > ptr->Writeable()){  
            length = ptr->Writeable();
        }
        //length = 8096  //TODU : 接收失败  
        std::cout << "fd : " << Socket_fd_ << std::endl; 
        int ret = recv(Socket_fd_,ptr->WritePtr(),static_cast<size_t>(length),flag);
/*         int ret = 0;
        while(true){ //全部都是接收失败
            ret = recv(Socket_fd_,ptr->WritePtr(),static_cast<size_t>(length),flag);
            if(ret == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) std::cout << "failed\n";
        } */
        //printf("errno :%d\n",errno);
        std::cout << "ret : " << ret << std::endl;//输出-1
        if(ret != -1) ptr->Write(ret);//顺便刷新已接收数据
        return ret;
    }

    int Socket::Read(char* Buffer, int length, int flag){
        return static_cast<int>(recv(Socket_fd_,static_cast<void*>(Buffer),
        static_cast<ssize_t>(length),flag));
    }

    int Socket::Write(char* Buffer, int length, int flag){
        return static_cast<int>(send(Socket_fd_,static_cast<void*>(Buffer),
        static_cast<ssize_t>(length),flag));
    }
}