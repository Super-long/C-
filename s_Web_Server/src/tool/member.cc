#include"member.h"
#include"../tool/userbuffer.h"
#include<memory>

namespace ws{
    void Member::DoRead(){
        int ret = 0;
        while(ret = Socket_Ptr->Read(User_Buffer) && ret > 0){}

        if(Http_Parser_->Finished()){ 
            Http_Parser_->Again_Parser();
        }
        Http_Parser_->Starting_Parser();
        //在这里时已经解析完成 信息存在request结构体中 可以开始转发
    }

    void Member::Init(){
        User_Buffer = std::make_shared<UserBuffer>(8096);
        Http_Parser_ = std::make_unique<HttpParser>(User_Buffer);
        Http_Request_ = std::make_unique<HttpRequest>(); 
    }

    bool Member::CloseAble() const{
        if(Http_Request_->Return_Flag != Keep_Alive && Http_Parser_->Finished()) return true;
        return false;
    }
}