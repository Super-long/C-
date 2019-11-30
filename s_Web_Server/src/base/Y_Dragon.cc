#include"Y_Dragon.h"

namespace Y_Dragon{
    //同一IP发送请求过多 或IP被列入黑名单 
    //文件权限不够
/*     bool IsForbidden(std::shared_ptr<ws::HttpRequest>){
    }
 */
    int MyPort(){
        return 8888;
    }

    int EventResult_Number(){
        return 8096;
    }
}