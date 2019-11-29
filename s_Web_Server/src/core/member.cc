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
        Http_Parser_->Starting_Parser();//解析
        if(Http_Parser_->Finished()){ //解析错误也是ok的
            Content_Provider_->Provide();
        }
        Write_Loop_->DoAll();
    }

    void Member::Init(){
        User_Buffer = std::make_shared<UserBuffer>(8096);
        Http_Parser_ = std::make_unique<HttpParser>(User_Buffer);
        Http_Request_ = std::make_unique<HttpRequest>(); 
        Write_Loop_ = std::make_shared<WriteLoop>(fd(), 8096);
        Content_Provider_ = std::make_unique<ContentProvider>(Http_Request_, Write_Loop_);
    }

    bool Member::CloseAble() const{
        if(Http_Request_->Return_Flag != Keep_Alive && Http_Parser_->Finished()) return true;
        return false;
    }
}