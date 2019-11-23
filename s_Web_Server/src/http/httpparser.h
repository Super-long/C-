#ifndef HTTPPARSER_H_
#define HTTPPARSER_H_

#include"../base/nocopy.h"
#include"../tool/basebuffer.h"
#include<memory>

namespace ws{

    class HttpParser : public Nocopy{
        public:
            
        private:
            std::unique_ptr<BaseBuffer> User_Buffer_;
    };

}

#endif