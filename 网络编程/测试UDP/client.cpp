 #include<iostream>
 #include<stdio.h>
 #include<sys/socket.h>
 #include<unistd.h>
 #include<sys/types.h>
 #include<netdb.h>
 #include<netinet/in.h>
 #include<arpa/inet.h>
 #include<string.h>


using namespace std;
int main()
{
        setvbuf(stdout,NULL,_IONBF,0);
        fflush(stdout);
        struct sockaddr_in addrto;
        bzero(&addrto,sizeof(struct sockaddr_in));
        addrto.sin_family=AF_INET;
        addrto.sin_addr.s_addr=htonl(INADDR_ANY);
        addrto.sin_port=htons(6000);
        socklen_t len=sizeof(addrto);
        int sock=-1;
        if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
        {
                cout<<"socket error..."<<endl;
                return -1;
        }
        const int opt=-1;
        int nb=0;
        nb=setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(char*)&opt,sizeof(opt));
        if(nb==-1)
        {
                cout<<"set socket errror..."<<endl;
                return -1;
        }
        if(bind(sock,(struct sockaddr*)&(addrto),len)==-1)
        {
                cout<<"bind error..."<<endl;
                return -1;
        }
        char msg[100]={0};
        while(1)
        {
                int ret=recvfrom(sock,msg,100,0,(struct sockaddr*)&addrto,&len);
                if(ret<=0)
                {
                        cout<<"read error..."<<endl;
                }
                else
                {
                        printf("%s\t",msg);
                }
                sleep(1);
        }
        return 0;
}
