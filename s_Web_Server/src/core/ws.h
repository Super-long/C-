#include"../net/epoll.h"
#include"server.h"
#include"manger.h"
namespace ws{
    class Web_Server{
        public:
            Web_Server();
            void Running();
        private:
            Manger _Manger_;
            Epoll _Epoll_;
            Server _Server_;
    };
}