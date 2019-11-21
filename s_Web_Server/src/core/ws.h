#include"../net/epoll.h"
namespace ws{
    class Web_Server{
        public:
            Web_Server();
            void Running();
        private:
            Epoll;
    };
}