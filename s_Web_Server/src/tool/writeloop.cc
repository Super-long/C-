#include"writeloop.h"
#include<cstdarg>

namespace ws{
    int WriteLoop::swrite(const char* format, ...){
        va_list va;
        va_start(va, format);
        int ret = User_Buffer_->SWrite(format, va);
        va_end(va);
        write(ret);
        return ret;
    }

    bool WriteLoop::SendFile(std::shared_ptr<FileReader> ptr){
        ssize_t len = 0;
        while(len = ptr->SendFile(fd_) && len > 0){}
        if(ptr->Send_End()){
            InsertSendFile(ptr);
            return false;
        }
        return true;
    }

    bool WriteLoop::DoFirst(){
        if(!Que.empty()) {
            auto Fun = Que.front();
            Que.pop_front();
            return Fun();
        }
        return false;
    }

}