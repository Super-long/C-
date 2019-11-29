#include"contentprovide.h"
#include"reaprovider.h"

namespace ws{
void ContentProvider::Provide(){
    if(!Pro) Pro = std::make_unique<REAProvider>(Http_Request, Write_Loop);
    Pro->provide();
}

}