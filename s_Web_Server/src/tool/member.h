#ifndef MEMBER_H_
#define MEMBER_H_

#include"../base/havefd.h"
#include"../base/nocopy.h"
#include<memory>
#include<algorithm>
#include"../core/socket.h"
#include"../tool/userbuffer.h"

namespace ws{
    class Member : public Nocopy,public Havefd{
        public:
            Member(int fd, int time) : Socket_Ptr(std::make_unique<Socket>(fd)),Time_Spot(time){}
            Member(std::unique_ptr<Socket>&& ptr, int time) : Time_Spot(time){
                std::swap(Socket_Ptr,ptr);
            }

            int fd() const final{return Socket_Ptr->fd();}

        private:
            std::unique_ptr<Socket> Socket_Ptr;
            
            std::unique_ptr<UserBuffer> User_Buffer;
            int Time_Spot;
    };
}


#endif 