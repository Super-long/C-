#include"socket.h"
#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>

namespace ws{
    int Socket::Close(){
        int rv = ::close(Socket_fd_);
        if(rv != -1) Have_Close_ = false;
        return rv;
    }

    inline int Socket::SetNoblocking(int flag){
        int old_option = fcntl(Socket_fd_,F_GETFL);
        int new_option = old_option | O_NONBLOCK | flag;
        fcntl(Socket_fd_,F_SETFL,new_option);
        return old_option;
    }

    inline int Socket::SetNoblockingCLOEXEC(){
        return Socket::SetNoblocking(O_CLOEXEC);
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