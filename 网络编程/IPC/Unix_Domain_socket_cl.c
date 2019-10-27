#include<sys/un.h>
#include<sys/socket.h>
#include<assert.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define SV_SOCKET_PATH "/home/lizhaolong/suanfa/C++/网络编程/IPC/c"
#define BUF_SIZE 100
#define BACKLOG 5

int main(int argc,char **argv){
    struct sockaddr_un addr;
    int sfd,cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    assert(sfd != -1);

    memset(&addr,0,sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SV_SOCKET_PATH,sizeof(addr.sun_path) - 1);
    printf("**%s**\n",addr.sun_path);

    if(connect(sfd,(struct sockaddr*)&addr,sizeof(struct sockaddr_un)) == -1) return 0;

    int sumread = 0,ret = 0;
    while((sumread = read(STDIN_FILENO,buf,BUF_SIZE-1)) > 0){
        buf[sumread-1] = '\0';
        printf("read : %s\n",buf);
        if(write(sfd,buf,numRead) != numRead){
            printf("%s\n",strerror(errno));
        }
        if((ret = send(sfd,buf,numRead,0) )!= numRead){
            //printf("%d\n",errno);//报错为地址错误
            printf("%s\n",strerror(errno));
        }
    }
    close(sfd);
}