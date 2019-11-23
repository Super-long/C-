#ifndef PARSED_HEADER_H_
#define PARSED_HEADER_H_

#include"../base/nocopy.h"
#include"basebuffer.h"
#include<memory>
#include<cstring>
#include<fstream>

namespace ws{

    class ParsedHeader : public Nocopy, public BaseBuffer{
        public:
            explicit ParsedHeader(const char* ptr) : length(strlen(ptr)),Header(ptr){}        
            ParsedHeader(const char* ptr,int len) :
                length(static_cast<size_t>(len)),Header(ptr){}
            

        private:
            const char* Header;//获取到的指针本来就是智能指针
            size_t length;
    };
    std::ostream& operator<<(std::ostream&, const ParsedHeader&);
}



#endif