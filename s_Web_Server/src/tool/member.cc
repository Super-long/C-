#include"member.h"

namespace ws{
    void Member::DoRead(){
        int ret = 0;
        while(ret = Socket_Ptr->Read(User_Buffer) && ret > 0){}

        if(Http_Parser_->Finished()){
            Http_Parser_->Again_Parser();
        }
        Http_Parser_->Starting_Parser();

        //在这里时已经解析完成
    }
}