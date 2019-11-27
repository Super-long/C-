 #ifndef CONTENTPROVIDER_H_
 #define CONTENTPROVIDER_H_

#include"../base/nocopy.h"
#include"../tool/writeloop.h"
#include"../http/httprequest.h"
#include"provider.h"
#include<memory>
namespace ws{

    class ContentProvider : public Nocopy{
        public:
            ContentProvider(std::shared_ptr<HttpRequest> Hr, std::shared_ptr<WriteLoop> Wl) : 
                Http_Request(Hr), Write_Loop(Wl) {} 
            void Provide();
        private:
            std::unique_ptr<Provider> Pro;
            std::shared_ptr<HttpRequest> Http_Request;
            std::shared_ptr<WriteLoop> Write_Loop;
    };
}

 #endif