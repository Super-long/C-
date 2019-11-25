#ifndef MEMBER_H_
#define MEMBER_H_

#include"../base/havefd.h"
#include"../base/nocopy.h"
#include<memory>
#include<algorithm>
#include"../core/socket.h"
#include"../tool/userbuffer.h"
#include"../http/httprequest.h"
#include"../http/httpparser.h"

namespace ws{
    class Member : public Nocopy,public Havefd{
        public:
            Member(int fd, long time) : Socket_Ptr(std::make_unique<Socket>(fd)),Time_Spot(time){Init();}
            Member(std::unique_ptr<Socket>&& ptr, long time) : Time_Spot(time){
                Init(); //抛错也不要紧
                std::swap(Socket_Ptr,ptr);
            }
            Member() = delete;
            long TimeSpot() const { return Time_Spot; }
            void Touch(long Time_) { Time_Spot = Time_; }

            void DoRead();
            void DoWrite(); 
            bool CloseAble() const;

            int fd() const final{return Socket_Ptr->fd();} 
            void Init();
        private:
            std::unique_ptr<HttpParser> Http_Parser_;
            std::unique_ptr<HttpRequest> Http_Request_;
            std::unique_ptr<Socket> Socket_Ptr;
            
            std::shared_ptr<UserBuffer> User_Buffer;
            long Time_Spot;
    };
}


#endif 