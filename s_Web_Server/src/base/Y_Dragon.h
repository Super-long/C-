#ifndef Y_DRAGON_H_
#define Y_DRAGON_H_


#include"../http/httprequest.h"
#include"../net/address.h"
#include<memory>

namespace Y_Dragon{

    constexpr const char* Version(){
        return "0.0";
    };
    //同一IP发送请求过多 或IP被列入黑名单
    //文件权限不够
    bool IsForbidden(std::shared_ptr<ws::HttpRequest>){
    }

    int MyPort(){
        return 8888;
    }

    int EventResult_Number(){
        return 8096;
    }
}

#endif