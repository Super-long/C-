#include"httprequest.h"

namespace ws{//TODO 改为值传递
    void HttpRequest::Store_Header(ParsedHeader header, ParsedHeader value){
        Header_Value.emplace(std::move(header), std::move(value)); 
    }

    ParsedHeader HttpRequest::Get_Value(const ParsedHeader& header) const{
        auto T = Header_Value.find(header);
        if(T != Header_Value.end()){   
            throw std::invalid_argument("'HttpRequest::GrtValue' No such user.");
        }
        //TODU 元素失效
        std::cout << "zhaodao\n";
        std::cout << T->second.Length() << std::endl;
        std::cout << "zhaodo\n";
        return T->second;
    }
}