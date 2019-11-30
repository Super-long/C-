#include"reaprovider.h"
#include"../../tool/parsed_header.h"
#include"../../tool/filereader.h"
#include"../../http/httpstatus.h"
namespace ws{

    void REAProvider::provide(){
        std::shared_ptr<FileReader> file = nullptr;
        bool cond = FileProvider(file);
        if(cond){
            int ret = RegularProvide(file->FileSize());//回复的内容的大小
            ret += WriteCRLF();
            _Write_Loop_->AddSend(ret);
            _Write_Loop_->AddSendFile(file);
            ret = WriteCRLF();
            _Write_Loop_->AddSend(ret);
        }else{
            ProvideError();
        }
    }

    bool REAProvider::FileProvider(std::shared_ptr<FileReader>& file){
        if(!Good()){
            _Request_->Set_StatusCode(HSCBadRequest);
            return false; //解析出现错误
        }
        //这一步得到了要解析的文件
        file = std::make_shared<FileReader>(static_cast<FileProxy>(_Request_->Get_Value(static_cast<ParsedHeader>("Host")).ReadPtr()), _Request_->Return_Uri().ReadPtr());

        if(!file->Fd_Good() || !file->IsTextFile()){
            _Request_->Set_StatusCode(HSCForbidden); 
            return true;
        }
        if(!file){
            _Request_->Set_StatusCode(HSCNotFound);
            return false;
        }
        _Request_->Set_StatusCode(HSCOK);
        return true;
    }
}