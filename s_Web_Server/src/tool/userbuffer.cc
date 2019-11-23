#include"userbuffer.h"
#include <cstring>
//#include <cstdarg>

namespace ws{
    void UserBuffer::Read(char* Start, int bytes) {
        if(Read_Spot + bytes > Buffer_Size){
            throw std::out_of_range("'UserBuffer::Read' Out ou range when reading.");
        }
        memcpy(Start,Buffer_.get() + Read_Spot, static_cast<size_t>(bytes));
        Read_Spot += static_cast<size_t>(bytes);
    }

    std::unique_ptr<char[]> UserBuffer::Read(int bytes){
        if(Read_Spot + bytes > Buffer_Size){
            throw std::out_of_range("'UserBuffer::Read' Out ou range when reading.");
        }
        std::unique_ptr<char[]> ptr(new char(Readable()));
        memcpy(ptr.get(), Buffer_.get() + Read_Spot, static_cast<size_t>(bytes));
        Read_Spot += static_cast<size_t>(bytes);
        return ptr;
    }

    char UserBuffer::Peek(int jump) const{
        if(Buffer_Size < Read_Spot + jump && Read_Spot + jump < 0 ){
            throw std::out_of_range("'UserBuffer::Peek' The parameter is not in the vaild range.");
        }
        return Buffer_[jump];
    }

    int UserBuffer::Write(char* Buf, int bytes){
        if(bytes > Writeable()){
            throw std::out_of_range("'UserBuffer::Write' The parameter is not in the valid range");
        }
        memcpy(Buffer_.get() + Write_Spot, Buf, static_cast<size_t>(bytes));
        Write_Spot += static_cast<size_t>(bytes);
        return bytes;
    }

    int UserBuffer::Write(const char* Buf, int bytes){
        if(bytes > Writeable()){
            throw std::out_of_range("'UserBuffer::Write' The parameter is not in the valid range");
        }
        memcpy(Buffer_.get() + Write_Spot, Buf, static_cast<size_t>(bytes));
        Write_Spot += static_cast<size_t>(bytes);
        return bytes;
    }

    int UserBuffer::Write(const std::string& str){
        size_t len = str.length();
        if(len > Writeable()){
            throw std::out_of_range("'UserBuffer::Write' The parameter is not in the valid range");
        }
        memcpy(Buffer_.get() + Write_Spot, str.c_str(), len);
        Write_Spot += len;
        return static_cast<int>(len);
    }

    void UserBuffer::Move_Buffer(){ //先试下有没有bug
        size_t inter = Write_Spot - Read_Spot;
        memcpy(Buffer_.get(), Buffer_.get() + Read_Spot, inter);
        Read_Spot = 0;
        Write_Spot = inter;
    }
}