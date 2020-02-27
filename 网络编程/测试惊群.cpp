#include<stdio.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<unistd.h>  
#include<sys/epoll.h>  
#include<netdb.h>  
#include<stdlib.h>  
#include<fcntl.h>  
#include<sys/wait.h>  
#include<errno.h>  
#define PROCESS_NUM 10  
#define MAXEVENTS 64  
//socket创建和绑定  
int sock_creat_bind(char * port){  
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);  
    struct sockaddr_in serveraddr;  
    serveraddr.sin_family = AF_INET;  
    serveraddr.sin_port = htons(atoi(port));  
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    bind(sock_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));  
    return sock_fd;  
}  
//利用fcntl设置文件或者函数调用的状态标志  
int make_nonblocking(int fd){  
    int val = fcntl(fd, F_GETFL);  
    val |= O_NONBLOCK;  
    if(fcntl(fd, F_SETFL, val) < 0){  
        perror("fcntl set");  
        return -1;  
    }  
    return 0;  
}  
  
int main(int argc, char *argv[])  
{  
    int sock_fd, epoll_fd;  
    struct epoll_event event;  
    struct epoll_event *events;  
          
    if(argc < 2){  
        printf("usage: [port] %s", argv[1]);  
        exit(1);  
    }  
     if((sock_fd = sock_creat_bind(argv[1])) < 0){  
        perror("socket and bind");  
        exit(1);  
    }  
    if(make_nonblocking(sock_fd) < 0){  
        perror("make non blocking");  
        exit(1);  
    }  
    if(listen(sock_fd, SOMAXCONN) < 0){  
        perror("listen");  
        exit(1);  
    }  
    if((epoll_fd = epoll_create(MAXEVENTS))< 0){  
        perror("epoll_create");  
        exit(1);  
    }  
    event.data.fd = sock_fd;  
    event.events = EPOLLIN;  
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &event) < 0){  
        perror("epoll_ctl");  
        exit(1);  
    }  
    /*buffer where events are returned*/  
    events = (epoll_event*)calloc(MAXEVENTS, sizeof(event));  
    int i;  
    for(i = 0; i < PROCESS_NUM; ++i){  
        int pid = fork();  
        if(pid == 0){  
            while(1){  
                int num, j;  
                num = epoll_wait(epoll_fd, events, MAXEVENTS, -1);  
                printf("process %d returnt from epoll_wait\n", getpid());  
                //sleep(2);  
                for(i = 0; i < num; ++i){  
                    if((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN))){  
                        fprintf(stderr, "epoll error\n");  
                        close(events[i].data.fd);  
                        continue;  
                    }else if(sock_fd == events[i].data.fd){  
                        //收到关于监听套接字的通知，意味着一盒或者多个传入连接  
                        struct sockaddr in_addr;  
                        socklen_t in_len = sizeof(in_addr);  
                        if(accept(sock_fd, &in_addr, &in_len) < 0){  
                            printf("process %d accept failed!\n", getpid());  
                        }else{  
                            printf("process %d accept successful!\n", getpid());  
                        }  
                    }  
                }  
            }  
        }  
    }  
    wait(0);  
    free(events);  
    close(sock_fd);  
    return 0;  
}  