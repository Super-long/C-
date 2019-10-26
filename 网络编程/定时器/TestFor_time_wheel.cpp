/*这个测试函数的作用实际上就是处理非活动链接
通过信号触发时间轮的tick函数*/
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
#include"time_wheel.h"
using namespace std;
using namespace Time_Wheel;

namespace{
    int pipefd[2];
    const int FD_LIMIT = 65535;
    const int MAX_EVENT_NUMBER = 1024;
    const int TIMESLOT = 5;
    time_wheel timer;
    bool stop_server = false;
    int epollfd;
    bool timeout = false; //是否执行超时函数
}

int setnonblocking(int fd){//套接字设置为非阻塞
    int old_option = fcntl(fd,F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
    return old_option;
}

void addfd(int epollfd,int fd){
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    setnonblocking(fd);
}

void sig_handler(int sig){
    int old_errno = errno;
    int msg = sig;
    send(pipefd[1],(char*)&msg,1,0);//为什么要使用tcp的数据发送函数
    errno = old_errno;
}

void addsig(int sig){
    struct sigaction sa;
    memset(&sa,0,sizeof(sa));
    sa.sa_handler = sig_handler; //我去　这个竟然可以
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig,&sa,nullptr) != -1);
}

void timer_hander(){
    timer.tick();
    alarm(TIMESLOT); //定时发送信号
}

void cd_func(std::shared_ptr<client_date> ptr){
    epoll_ctl(epollfd,EPOLL_CTL_DEL,ptr->socked,0);
    close(ptr->socked);
    std::cout << "close fd : " << ptr->socked << endl; 
}

int main(int argc,char **argv){
    if(argc <= 2){
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
    assert(ret >= 0);

    ret = listen(listenfd,5);
    assert(ret >= 0);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5); 
    assert(epollfd != -1); 
    addfd(epollfd,listenfd);
    
    //创建未命名的全双工管道 第四个参数返回管道两端的socket描述符
    ret = socketpair(PF_UNIX,SOCK_STREAM,0,pipefd);
    assert(ret != -1);
    setnonblocking(pipefd[1]);//写端
    addfd(epollfd,pipefd[0]);

    addsig(SIGALRM);
    addsig(SIGTERM);

    vector<std::shared_ptr<client_date>> users(FD_LIMIT);
    bool timeput = false;
    alarm(TIMESLOT);
    while(!stop_server){
        int number = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
        if(number < 0 && errno != EINTR){ //第二个错误类型有点意思(被中断的系统调用)
            std::cout << "epoll errno\n";
            break;
        }
        for(int i=0;i<number;++i){
            int sockfd = events[i].data.fd;
            if(sockfd == listenfd){
                struct sockaddr_in client_address;
                bzero(&client_address,sizeof(client_address));
                socklen_t client_addrlength = sizeof(client_address);
                int connfd = accept(listenfd,(struct sockaddr*)&client_address,&client_addrlength);
                //设置用户设置
                addfd(epollfd,connfd);
                users[connfd] = make_shared<client_date>();
                users[connfd]->address =client_address;
                users[connfd]->socked = connfd;
                auto itr = timer.add_timer(TIMESLOT);
                users[connfd]->ptr = itr;
                //itr->get()->cb_func = cd_func;//注册回调函数
                (*itr)->cb_func = cd_func;
                (*itr)->cd = users[connfd];
                //itr->get()->cd = users[connfd];
            }else if((sockfd == pipefd[0]) && (events[i].events & EPOLLIN)){//信号事件
                int sig = 0;
                char signals[1024];
                ret = recv(pipefd[0],signals,sizeof(signals),0);
                if(ret == -1){
                    std::cout << "error in signal recv\n";
                }else if(ret == 0){
                    continue; //对端关闭会返回零
                }else{
                    for(int i=0;i<ret;++i){
                        switch (signals[i])
                        {
                            case SIGALRM:
                                timeout = true;
                                break;
                            case SIGTERM:
                                stop_server = true;
                                break;
                            default:
                                std::cout << "This signal is undefine behavior in this demo!\n";
                                break;
                        }
                    }
                }
            }else if(events[i].events & EPOLLIN){//处理用户接收到的数据
                cout << sockfd << endl;
                memset(users[sockfd]->buf,'\0',sizeof(users[sockfd]->buf));
                ret = recv(sockfd,users[sockfd]->buf,BUFFER_SIZE-1,0);
                std::cout << "get " << ret << " bytes of clint data " 
                << users[sockfd]->buf << " from " << sockfd << endl; 
                auto ptr = users[sockfd]->ptr;
                if(ret < 0){
                    if(errno != EAGAIN){
                        cd_func(users[sockfd]);
                        timer.del_timer(users[sockfd]->ptr);//删除定时器
                    }
                }else if(ret == 0){
                    //相当于关闭连接　服务器也关闭连接即可
                    cd_func(users[sockfd]);
                    timer.del_timer(users[sockfd]->ptr);
                }else{//当有数据可读的时候　我们需要调整定时器
                    time_t cur = time(nullptr);
                    timer.del_timer(users[sockfd]->ptr);
                    auto ptr = timer.add_timer(cur);
                    users[sockfd]->ptr = ptr;
                    ptr->get()->cd = users[sockfd];
                    ptr->get()->cb_func = cd_func;
                } 
            }   
        }
        if(timeout){
            timer_hander(); //执行回调函数　把超时的连接断开　
            timeout = false;
        }
    }
    close(listenfd);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}