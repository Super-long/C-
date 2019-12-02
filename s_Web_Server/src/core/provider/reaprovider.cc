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
            std::cout << _Request_->Return_Flag() << std::endl;
            _Request_->Set_StatusCode(HSCBadRequest);
            return false; //解析出现错误
        }
        //往上 解析完成 参数传递成功
        std::cout << "创建filereader\n"; 
        //TODO Get_Value这个函数错误
        char* path = "graph.dot"; 
        char* Host = "Host";
        ParsedHeader H(Host);
        auto x = _Request_->Get_Value(H);
        std::cout << "ok\n";
        file = std::make_shared<FileReader>                                                             //_Request_->Return_Uri().ReadPtr()
        (static_cast<FileProxy>(_Request_->Get_Value(static_cast<ParsedHeader>("Host")).ReadPtr()), path); 
 
        std::cout << "文件打开完成\n";
        if(!file->Fd_Good() || !file->IsTextFile()){
            _Request_->Set_StatusCode(HSCForbidden); 
            return false;
        }
        if(!file){
            _Request_->Set_StatusCode(HSCNotFound);
            return false;
        }
        _Request_->Set_StatusCode(HSCOK);
        return true;
    }
}