#include"provider.h"
#include"../base/Y_Dragon.h"


namespace ws{
    bool Provider::IsFilename(char x) const {
        return !(x == '?' || x == '\\' || x == '/' || x == '*' ||
        x == '\"' || x == '\'' || x == '<' || x == '>' || x == '|');
    }

    int Provider::WriteHead(int ma, int mi, const HttpStatusCode& code){
        auto T = static_cast<int>(code);
        int ret = _Write_Loop_->swrite("HTTP/%d.%d %d %s\r\n",ma, mi, T, StatusCode_to_String(T));
        ret += _Write_Loop_->swrite("Server: Y_Dragon %s\r\n",Y_Dragon::Version());
        return ret;
    }

    int Provider::WriteDate(){
        time_t t = time(nullptr);
        char buf[100]; //很好的计算时间的函数
        strftime(buf, 70, "Date: %a, %d %b %Y %H: %M:%S GMT\r\n", gmtime(&t));
        return _Write_Loop_->swrite(buf);
    }

    int Provider::WriteItem(const char* key, const char* va){
        return _Write_Loop_->swrite(key, va);
    }

    int Provider::WriteConnection(){
        return _Write_Loop_->swrite("Connection", 
        _Request_->Return_Flag() == Keep_Alive ? "Keep-alive" : "Close");
    }

    int Provider::WriteCRLF(){
        return _Write_Loop_->swrite("/r/n", 2);
    } 

    

}