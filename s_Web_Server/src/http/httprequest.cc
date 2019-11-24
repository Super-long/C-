#include"httprequest.h"

namespace ws{
    inline void HttpRequest::Store_Header(const ParsedHeader& header, const ParsedHeader& value){
        Header_Value.emplace(header, value);
    }

    ParsedHeader HttpRequest::Get_Value(const ParsedHeader& header) const{
        auto T = Header_Value.find(header);
        if(T == Header_Value.end()){
            throw std::invalid_argument("'HttpRequest::GrtValue' No such user.");
        }
        return T->second;
    }
}