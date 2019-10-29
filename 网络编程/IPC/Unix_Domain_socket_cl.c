#include<sys/un.h>
#include<sys/socket.h>
#include<assert.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define SV_SOCKET_PATH "/home/lizhaolong/suanfa/C++/网络编程/IPC/c"
//当上面这个路径设置为nullptr时也可以运行  linux抽象socket名空间
//1.在文件系统不具备写权限时比较有用 
//2.不需要担心与文件系统中的现有名称冲突
//ps:当BUF_SIZE较小时不会截断 在客户端可以做一个处理 进行分块 又不是因为网络原因 当然是写多少就发多少了 (稳定)
#define BUF_SIZE 10
#define BACKLOG 5

int main(int argc,char **argv){
    struct sockaddr_un addr;
    int sfd,cfd;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    assert(sfd != -1);

    memset(&addr,0,sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SV_SOCKET_PATH,sizeof(addr.sun_path) - 1);

    int re = 0;
    if((re = connect(sfd,(struct sockaddr*)&addr,sizeof(struct sockaddr_un))) == -1) return 0;
    printf("re : %d\n",re);
    int sumread = 0,ret = 0;
    while((sumread = read(STDIN_FILENO,buf,BUF_SIZE-1)) > 0){
        buf[sumread-1] = '\0';
        printf("read : %s\n",buf);
        if((ret = send(sfd,buf,sumread,0) )!= sumread){
            //printf("%d\n",errno);//报错为地址错误
            printf("ret%s\n",strerror(errno));
        }
    }
    close(sfd);
}