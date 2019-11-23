#include"httpparser.h"
#include"httpstatus.h"

namespace ws{
    void HttpParser::Again_Parser(){
        User_Buffer_->Clean();
        Parser_Result.release();
        Parser_Result = std::make_unique<HttpParser_Content>();
    }

    HttpParserFault HttpParser::Starting_Parser(){
        if(!Parser_able()){
            Parser_Result->Fault = HPFToLittleMessage;
        }
        Parsering();
        Requesting(); 
        return Parser_Result->Fault;
    }

    bool HttpParser::Parsering(){
        
    }
}