/*这个测试函数的作用实际上就是处理非活动链接
通过信号触发时间轮的tick函数　注意为信号处理函数的处理时间jia*/
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
    int epollfd;
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
    sa.sa_restorer = sig_handler;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig,&sa,nullptr) != -1);
}

int main(){
    
}