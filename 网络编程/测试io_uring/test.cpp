#include <liburing.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

#include <sys/epoll.h>

// 用IOuring最大的问题是如何用接口接收网络套接字？
// 如果监听ring_fd，就没必要用epoll，直接poll或者select就可以，
// 但是监听ring_fd我们只能判断一次来了几个事件，没办法判断事件的类型，这意味着没办法判断套接字何时关闭

int main()
{
    struct io_uring ring;
    io_uring_queue_init(32, &ring, 0);

    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring); // 队列满的时候会返回nullptr
    int fd = open("test.txt", O_WRONLY | O_CREAT);
    char array[] = "Hello world";
    struct iovec iov = {
        .iov_base = array,
        .iov_len = strlen(array),
    };
    io_uring_prep_writev(sqe, fd, &iov, 1, 0);

    int ret = io_uring_submit(&ring);
    std::cout << "ret = " << ret << std::endl;
    //----------------------------------------------------

    sqe = io_uring_get_sqe(&ring);
    int fd2 = open("test2.txt", O_WRONLY | O_CREAT);
    struct iovec iov2 = {
        .iov_base = array,
        .iov_len = strlen(array),
    };
    io_uring_prep_writev(sqe, fd2, &iov2, 1, 0);
    ret = 0;
    ret = io_uring_submit(&ring);
    std::cout << "ret = " << ret << std::endl;
    // -----------------------
    struct epoll_event ev,events[20];

    int epfd=epoll_create(10000); //创建epoll句柄
    ev.data.fd=ring.ring_fd;
    //设置要处理的事件类型
    ev.events=EPOLLIN;
    //注册epoll事件
    epoll_ctl(epfd,EPOLL_CTL_ADD,ring.ring_fd,&ev);
    int nfds=epoll_wait(epfd,events,20,1000);
    for(int i=0;i<nfds;++i)
    {
        if(events[i].data.fd==ring.ring_fd)
        {
            struct io_uring_cqe *cqe;
            io_uring_peek_cqe(&ring, &cqe);
            
            if (!cqe) {
            puts("Waiting...");
            // accept 新连接，做其他事
            } else {
                puts("Finished.");
            }
            std::cout << cqe->res << std::endl;
            std::cout << cqe->flags << std::endl;
            io_uring_cqe_seen(&ring, cqe);  
            cqe = nullptr;


            io_uring_peek_cqe(&ring, &cqe);
            
            if (!cqe) {
            puts("Waiting...");
            // accept 新连接，做其他事
            } else {
                puts("Finished.");
            }

            std::cout << cqe->res << std::endl;
            std::cout << cqe->flags << std::endl;
            io_uring_cqe_seen(&ring, cqe);  
            cqe = nullptr;



            io_uring_peek_cqe(&ring, &cqe);
            
            if (!cqe) {
            puts("Waiting...");
            // accept 新连接，做其他事
            } else {
                puts("Finished.");
            }

            io_uring_cqe_seen(&ring, cqe);  
            cqe = nullptr;


            
            io_uring_peek_cqe(&ring, &cqe);
            
            if (!cqe) {
            puts("Waiting...");
            // accept 新连接，做其他事
            } else {
                puts("Finished.");
            }

            io_uring_cqe_seen(&ring, cqe);  // 标记n事件已经被处理
        }
    }

    //struct io_uring_cqe *cqe;
    io_uring_queue_exit(&ring);
}