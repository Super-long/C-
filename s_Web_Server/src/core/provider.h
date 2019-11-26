#ifndef PROVIDER_H_
#define PROVIDER_H_

#include"../base/copyable.h"
#include"../http/httprequest.h"
#include"../tool/writeloop.h"
#include"../http/httpstatus.h"
#include<memory>


namespace ws{
    class Provider : public Copyable{
        public:
            Provider(std::shared_ptr<HttpRequest> Hr,
                     std::shared_ptr<WriteLoop> Wl) : _Request_(std::move(Hr)), _Write_Loop_(std::move(Wl)){}
            int WriteHead(int, int, const HttpStatusCode& );
            //这里应该是协议版本　服务器版本
            int WriteItem(const char*, const char*);
            //这里要写的是项
            int WriteConnection();
            //是否是长连接
            int WriteDate();//时间
            int WriteCRLF();
            //写上一个空行

            int ProvideError(); //错误的情况所要写的东西 
            int RegularProvide(bool, long);//多出来的参数用于content-type
            int RegularProvide(bool, long, const char*);

            const char* AutoAdapt() const{}
            constexpr const char* defaultMIME() const{return "text/html";}//实在是没什么呀
            bool IsFilename(char) const;
        protected:

            std::shared_ptr<HttpRequest> _Request_;
            std::shared_ptr<WriteLoop> _Write_Loop_;
    };
}

#endif 