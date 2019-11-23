#include"../net/epoll.h"
#include"server.h"
namespace ws{
    class Web_Server{
        public:
            Web_Server();
            void Running();
        private:
            Epoll _Epoll_;
            Server _Server_;
    };
}