#include<sys/un.h>
#include<sys/socket.h>
#include<assert.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define SV_SOCKET_PATH "/home/lizhaolong/suanfa/C++/网络编程/IPC/c"
#define BUF_SIZE 10
#define BACKLOG 5

int main(int argc,char **argv){
    struct sockaddr_un addr;
    int sfd,cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    assert(sfd != -1);

    if((remove(SV_SOCKET_PATH) == -1) && errno != ENOENT) return 0;

    memset(&addr,0,sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SV_SOCKET_PATH,sizeof(addr.sun_path) - 1);

    printf("uinjo\n");
    int ret = bind(sfd,(struct scokaddr*)&addr,sizeof(struct sockaddr_un));
    assert(ret != -1);

    printf("asdasd\n");
    ret = listen(sfd,BACKLOG);
    assert(ret != -1);
    printf("plplp\n");
    for(;;){
        printf("blocking!\n");
        cfd = accept(sfd,NULL,NULL);
        printf("连接成功\n");
        assert(cfd != -1);

        int numRead = 0;
        while(numRead = read(cfd,buf,BUF_SIZE)){
            printf("get %d :  %s\n",numRead,buf);
            write(STDOUT_FILENO,buf,numRead);
        }
        close(cfd);
    }
}