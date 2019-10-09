//测试LT与ET模式
//显然相比之下ET事件被触发的次数少于LT 少了内核态向用户态拷贝就绪队列
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<errno.h> 
#include<fcntl.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<signal.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFERSIZE 10

int SetNonblock(int fd){ //套接字设置为非阻塞
    int old_option = fcntl(fd,F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
    return old_option;
}

void addfd(int epollfd,int fd,int enable_et){
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;//可读
    if(enable_et){
        ev.events |= EPOLLET;
    }
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
    SetNonblock(fd);
}

void lt(struct epoll_event* events,int number,int epollfd,int listenfd){
    char BUF[BUFFERSIZE];
    for(int i=0;i<number;++i){
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd){ //说明是连接请求
            struct sockaddr_in Client_Address;
            socklen_t Client_Addrlength = sizeof(Client_Address);
            int connfd = accept(listenfd,(struct sockaddr*)&Client_Address,&Client_Addrlength);
            addfd(epollfd,connfd,0); 
        }else if(events[i].events & EPOLLIN){//套接字上发来的可读事件
            printf("收到消息 i :: %d\n",i);
            memset(BUF,'\0',sizeof(BUF));
            int ret = recv(sockfd,BUF,BUFFERSIZE,MSG_WAITALL);
            if(ret <= 0){
                close(sockfd);
                continue;
            }
            printf("get %d bytes of content : %s\n",ret,BUF);
        }else{
            printf("奇怪的事情　不是可读事件\n");
        }
    }
}

void et(struct epoll_event* events,int number,int epollfd,int listenfd){
    char BUF[BUFFERSIZE];
    for(int i=0;i<number;++i){
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd){ //说明是连接请求
            struct sockaddr_in Client_Address;
            socklen_t Client_Addrlength = sizeof(Client_Address);
            int connfd = accept(listenfd,(struct sockaddr*)&Client_Address,&Client_Addrlength);
            addfd(epollfd,connfd,1); //对于连接请求设置为ET 
        }else if(events[i].events & EPOLLIN){
            printf("收到消息 i:: %d\n",i);
            while(1){
                memset(BUF,'\0',sizeof(BUF));
                int ret = recv(sockfd,BUF,BUFFERSIZE,0);
                if(ret < 0){//非阻塞io会触发这两个错误　查下
                    if((errno == EAGAIN) || (errno == EWOULDBLOCK)){
                        printf("read later\n");
                        break; //证明数据已经读取完毕
                    }
                    close(sockfd);
                    break;
                }else if(ret == 0){ //关闭请求
                    close(sockfd);
                }else{
                    printf("get %d bytes of content : %s\n",ret,BUF);
                }
            }
        }else{
            printf("奇怪的事情　不是可读事件\n");
        }
    }
}

int main(int argc,char **argv){
    if(argc <= 2){
        printf("paramater error \n");
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET,SOCK_STREAM,0);
    assert(listenfd >= 0);

    ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd,5);
    assert(ret != -1);

    struct epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    addfd(epollfd,listenfd,1);

    while(1){
        int ret = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,NULL);
        if(ret < 0){
            printf("error in epoll\n");
            continue;
        }
        //lt(events,ret,epollfd,listenfd);
        et(events,ret,epollfd,listenfd);
    }
    close(listenfd);
    return 0;
}