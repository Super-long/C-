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

}