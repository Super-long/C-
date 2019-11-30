#include"socket.h"


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
        int ret = static_cast<int>(recv(Socket_fd_,ptr->WritePtr(),length,flag));
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